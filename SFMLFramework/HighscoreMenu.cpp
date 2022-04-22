#include <conio.h>
#include <functional>

#include "Game.h"
#include "Helpers.h"
#include "HighscoreMenu.h"
#include "MainGame.h"
#include "Player.h"
#include "TextureHandler.h"

HighscoreMenu::HighscoreMenu()
{
	m_pRenderWindow			= nullptr;
	m_pGame					= nullptr;
	m_pMainGame				= nullptr;
	m_pPlayer				= nullptr;
	m_pTextureHandler		= nullptr;

	m_pCursor				= new GameSprite();

	m_pHighscore			= new GameText();
	m_pEnterName			= new GameText();
	m_pPlayerName			= new GameText();
	m_pHighscoreName		= new GameText[21];
	m_pHighscoreScore		= new GameText[21];
	m_returnToMenu			= new GameText();

	m_flashTimer			= 0;
	m_cursorTimer			= 0;

	m_characterEntered		= 0;

	m_isBackspacePressed	= false;
	m_isEnterPressed		= false;
	m_cursorFlash			= false;
	m_nameEntered			= false;

	loadHighscoresFromFile();
}

HighscoreMenu::~HighscoreMenu()
{
	// Safe delete all pointers.
	safeDeletePointer(m_pCursor);
	safeDeletePointer(m_pHighscore);
	safeDeletePointer(m_pEnterName);
	safeDeletePointer(m_pPlayerName);
	safeDeletePointerArray(m_pHighscoreName);
	safeDeletePointerArray(m_pHighscoreScore);
	safeDeletePointer(m_returnToMenu);
}

void HighscoreMenu::initialise(Game* pGame, MainGame* pMainGame, TextureHandler* pTextureHandler, sf::RenderWindow* pRenderWindow, Player* pPlayer)
{
	// Set all pointer references.
	m_pGame = pGame;
	m_pMainGame = pMainGame;
	m_pTextureHandler = pTextureHandler;
	m_pCursor->setTexture(m_pTextureHandler->getTexture(TextureType::Cursor));
	m_pPlayer = pPlayer;
	m_pRenderWindow = pRenderWindow;
	m_pRenderWindow->setKeyRepeatEnabled(false);

	//Set the starting positions of the Game Text on the highscore menu.
	float xPos = 150;
	float yPos = 250;

	m_pHighscore->initialise(Fonts::SciFi);
	m_pHighscore->setString("Highscores");
	m_pHighscore->setPosition(125, 50);
	m_pHighscore->setCharacterSize(110);

	m_pEnterName->initialise(Fonts::SciFi);
	m_pEnterName->setString("Enter your name");
	m_pEnterName->setPosition(175, 700);
	m_pEnterName->setCharacterSize(60);

	m_pPlayerName->initialise(Fonts::SciFi);
	m_pPlayerName->setPosition(325, 800);
	m_pPlayerName->setCharacterSize(60);
	m_pPlayerName->setLetterSpacing(3);
	
	m_returnToMenu->initialise(Fonts::SciFi);
	m_returnToMenu->setPosition(225, 700);
	m_returnToMenu->setCharacterSize(50);
	m_returnToMenu->setFillColor(sf::Color(0, 100, 0, 255));
	m_returnToMenu->setString("Press enter to\nreturn to menu");

	// Generate the name and score game text handles ready for when the highscores are loaded.
	for (int i = 0; i < 21; i++)
	{
		m_pHighscoreName[i].initialise(Fonts::SciFi);
		m_pHighscoreScore[i].initialise(Fonts::Jersey);

		m_pHighscoreName[i].setPosition(xPos, yPos);
		m_pHighscoreScore[i].setPosition(xPos + 150, yPos);

		m_pHighscoreName[i].setCharacterSize(40);
		m_pHighscoreScore[i].setCharacterSize(40);
		yPos += 40;

		// As there are to be two colums (10 highscore values per column), on the 10th iteration chance the position of where they are positioned.
		if (i == 9)
		{
			xPos = 475;
			yPos = 250;
		}
	}
	// Sort highscores from the file.
	sortHighscores();
	// Display the highscores loaded from the previous function.
	displayHighscores();
}

void HighscoreMenu::update(float deltaTime)
{
	// Check for user input.
	userInput();
	// Flash effect for the highscore title.
	flashEffect(deltaTime);
	// Flash and position cursor.
	cursorHandler(deltaTime);
}

void HighscoreMenu::render(sf::RenderTarget* window)
{
	// Render all names and highscores to the screen.
	for (int i = 0; i < 20; i++)
	{
		m_pHighscoreName[i].render(window);
		m_pHighscoreScore[i].render(window);
	}
	// Render the highscore title to the screen.
	m_pHighscore->render(window);

	// If the name has not yet been entered, display the 'Enter Name' text to the player (this will not show if directed to the highscores from the Main Menu.
	if (m_nameEntered == false)
	{
		m_pEnterName->render(window);
		m_pPlayerName->render(window);
	}
	else
	{
		// If the player has entered their name, return to menu instructions will show.
		m_returnToMenu->render(window);
	}

	// Draw cursor to the screen.
	if (m_cursorFlash == true && m_nameEntered == false)
	{
		window->draw(*m_pCursor);
	}
}

// Sorter for highscores that organised the array in descending order.
bool arrangeHighscores(HighscoreData b1, HighscoreData b2) {
	if (b1.score > b2.score) {
		return true;
	} 
	return false;
}

void HighscoreMenu::userInput()
{
	sf::Event			event;

	// Checks for event while the game is running.
	while (m_pRenderWindow->pollEvent(event))
	{
		// Check for if the 'BACKSPACE' button is pressed.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && m_characterEntered > 0 &&m_characterEntered < 5 && m_isBackspacePressed == false)
		{
			m_isBackspacePressed = true;
			m_characterEntered -= 1;
			// Removes the last character from the string.
			m_name.pop_back();
			// Sets the Gametext string.
			m_pPlayerName->setString(m_name);
		}
		else
		{
			m_isBackspacePressed = false;
		}

		// If the game window is close then this will exit the application correctly.
		if (event.type == sf::Event::Closed)
		{
			m_pRenderWindow->close();
		}

		// Check for if the player enters text other than 'BACKSPACE' and 'ENTER'.
		if (event.type == sf::Event::TextEntered && m_characterEntered < 4 && event.text.unicode != 8 && event.text.unicode != 13)
		{
			m_characterEntered += 1;
			// Add the key pressed to the string.
			m_name += char(event.text.unicode);
			// Sets the Gametext string.
			m_pPlayerName->setString(m_name);
		}

		// Check for if the player has pressed 'ENTER'.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_isEnterPressed == false)
		{
			if (m_characterEntered == 4 && m_nameEntered == false)
			{
				m_nameEntered = true;
				m_isEnterPressed = true;
				// Stores the name entered by the player in the last item in the array.
				m_highscoreData[20].name = m_name;
				// Stores the score achieved by the player in the last item in the array.
				m_highscoreData[20].score = m_pPlayer->getScore();
				// Re-sort the highscores to see if the player made it onto the board.
				sortHighscores();
			}

			// If the player has entered their name and wants to return to the main menu, this will allow them.
			if(m_nameEntered == true && m_isEnterPressed == false)
			{
				m_isEnterPressed = true;
				// Redirect the player to the main menu.
				m_pGame->setCurrentState(GameStates::StartMenu);
			}
		}
		else
		{
			m_isEnterPressed = false;
		}
	}
}

void HighscoreMenu::loadHighscoresFromFile()
{
	// Access the highscore file stored in the project files.
	std::ifstream mapFile("Highscore/Highscores.txt");


	for (int rowIndex = 0; rowIndex < 20; rowIndex++) //Loop for the amount of rows.
	{
		std::string fileRow; //Grab current file row in the text file.
		std::getline(mapFile, fileRow);

		std::stringstream stringstream(fileRow); //Grab strings within the current row.

		for (int fileColumn = 0; fileColumn < 2; fileColumn++) //Loop for the amount of columns.
		{
			std::string mapElement;
			std::getline(stringstream, mapElement, ':'); //Seperate strings by ':'.

			std::stringstream converter(mapElement); //Convert data gathered, ready to input into an array.
			
			// Sort the data gathered from the highscore file into a data struct array.
			switch (fileColumn)
			{
			case 0:
				converter >> m_highscoreData[rowIndex].name;
				break;
			case 1:
				converter >> m_highscoreData[rowIndex].score;
				break;
			}
		}
	}
}

void HighscoreMenu::writeHighscoresToFile()
{
	std::ofstream highscoreFile;
	// Open the highscore file.
	highscoreFile.open("Highscore/Highscores.txt");

	// Loop through all data stored in the struct array and store it in the highscore file.
	for (int i = 0; i < 21; i++)
	{
		highscoreFile << m_highscoreData[i].name << ":" << m_highscoreData[i].score << "\n";
	}

	//Reload the highscores onto the window so the player can see if they made it onto the board.
	displayHighscores();
	highscoreFile.close();
}

void HighscoreMenu::sortHighscores()
{
	// Sort the highscore into descending order.
	std::sort(m_highscoreData, m_highscoreData + 21, arrangeHighscores);
	writeHighscoresToFile();
}

void HighscoreMenu::displayHighscores()
{
	// Display all the data stored in the struct array as a game text object so the player can see.
	for (int i = 0; i < 20; i++)
	{
		if (m_highscoreData[i].score != 0)
		{
			std::string score = std::to_string(m_highscoreData[i].score);

			m_pHighscoreName[i].setString(m_highscoreData[i].name);
			m_pHighscoreScore[i].setString(score);
		}
	}

	// Highlight the new entry if the player made it onto the board.
	colorNewHighscoreEntry();
}

void HighscoreMenu::flashEffect(float deltaTime)
{
	// Start increasing the flas timer.
	m_flashTimer += deltaTime;

	// 0.2f is the time before a new color is generated.
	if (m_flashTimer > 0.2f)
	{
		// Randomly generate a new color.
		m_flashTimer = 0;
		int r = 0;
		int g = 0;
		int b = 0;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;

		// Set the color of the highscore gametext based on random values generated.
		m_pHighscore->setFillColor(sf::Color(r, g, b, 255));
	}
}

void HighscoreMenu::colorNewHighscoreEntry()
{
	// Color the new entry if the player made it onto the board so that they can see their score and position.
	for (int i = 0; i < 20; i++)
	{
		if (m_highscoreData[i].name == m_name && m_highscoreData[i].score == m_pPlayer->getScore())
		{
			m_pHighscoreName[i].setFillColor(sf::Color(0, 255, 0, 255));
			m_pHighscoreScore[i].setFillColor(sf::Color(0, 255, 0, 255));
			return;
		}
	}
}

void HighscoreMenu::cursorHandler(float deltaTime)
{
	// Timer for the flash counter.
	m_cursorTimer += deltaTime;

	// Flash the cursor every 0.5 seconds.
	if (m_cursorTimer > 0.5f)
	{
		m_cursorTimer = 0;
		m_cursorFlash = !m_cursorFlash;
	}

	// Set the position of the cursor based on how many characters have been entered.
	switch (m_characterEntered)
	{
	case 0:
		m_pCursor->setPosition(310,860);
		break;
	case 1:
		m_pCursor->setPosition(350,860);
		break;
	case 2:
		m_pCursor->setPosition(390,860);
		break;
	case 3:
		m_pCursor->setPosition(430,860);
		break;
	case 4:
		m_pCursor->setPosition(430,10000);
		break;
	}
}

// Setter for displaying 'ENTER NAME' or not.
void HighscoreMenu::returnToMenu(bool canReturn)
{
	m_nameEntered = canReturn;
}
