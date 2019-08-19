
class EditorState :
	public State
{
private:
	//변수
	sf::Font font;
	std::map<std::string, Button* > buttons;
	sf::Texture	tx;

	//초기화함수
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initBackground();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~EditorState();

	//업데이트함수
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

};

