#pragma once

class ScoreManager
{
private:
	ScoreManager() {}
	~ScoreManager() {}

public:
	static ScoreManager& Instance()
	{
		static ScoreManager instance;
		return instance;
	}

	void Update() {}
	void Render() {}
	void add(int point) { score += point; }
	void setScore(int point) { score = point; }
	void resetScore(int point) { score = 0; }

	int getScore() { return score; }

private:
	
	int score = 0;
};
