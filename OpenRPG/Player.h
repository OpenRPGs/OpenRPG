
class Player :
	public Entity
{
private:
	//Variables
	bool attacking;
	int* window_focus;
	//Initializer functions
	void initVariables();
	void initComponents();
public:
	Player(float x, float y, sf::Texture& texture, int& window_focus);
	virtual ~Player();

	//Functions
	void updateAttack();
	void updateAnimation(const float& dt);
	virtual void update(const float& dt);
};
