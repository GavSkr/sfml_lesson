#include "Snake.h"

Snake::Snake(const int x, const int y)
{
	head.setSize({ 10, 10 });
	head.setFillColor(sf::Color::Green);
	head.setPosition(x, y);
}

sf::Vector2f Snake::getSize_head()
{
	return this->head.getSize();
}

sf::Vector2f Snake::getPosition_head()
{
	return this->head.getPosition();
}

void Snake::setPosition(const sf::Vector2f position)
{
	sf::Vector2f h_p = head.getPosition();
	if(position.x >= 0 && position.y >= 0)
		head.setPosition(position);
	else
		head.setPosition(0, 0);
	if (body.size())
		for (auto &i : body)
			i.setPosition(i.getPosition().x + (position.x-h_p.x), i.getPosition().y + (position.y - h_p.y));
}

void Snake::setPosition(const float x, const float y)
{
	//sf::Vector2f h_p = head.getPosition();
  	int dx = x - head.getPosition().x;
	int dy = y - head.getPosition().y;
	if (x >= 0 && y >= 0)
	{
		head.setPosition(x, y); 
		//if (body.size())
		//	for (auto &i : body)
		//		i.setPosition(i.getPosition().x + dx, i.getPosition().y + dy);
	}
	else
	{
		head.setPosition(300, 300);
		//if (body.size())
		//	for (auto& i : body)
		//		i.setPosition(i.getPosition().x + dx, i.getPosition().y + dy);
	}
}

void Snake::grow(const int x, const int y)
{
	if (check_move(x, y))
	{
		sf::RectangleShape snake_neck = head;
		snake_neck.setFillColor(sf::Color::Red);
		body.push_back(snake_neck);
		head.setPosition(head.getPosition().x + step[x], head.getPosition().y + step[y]);
	}
	if (body.size() == 10)
		body.pop_front();
}

void Snake::grow()
{
	if (check_move())
	{
		sf::RectangleShape snake_neck = head;
		snake_neck.setFillColor(sf::Color::Red);
		body.push_back(snake_neck);
		head.setPosition(head.getPosition().x + x, head.getPosition().y + y);
	}
}

int Snake::size()
{
	return body.size() + 1;
}

void Snake::move_auto(const int x, const int y)
{
	if (false)//(live == 10)
	{
		grow(x, y);
		live = 0;
	}
	else
	{
		if (check_move(x, y))
		{
			++live;
			if (body.size())
			{
				grow();
				body.pop_front();
			}
			else
				head.setPosition(head.getPosition().x + step[x], head.getPosition().y + step[y]);
		}
	}
}

void Snake::move_auto()
{
	if (body.size())
	{
		grow();
		body.pop_front();
	}
	else
		head.setPosition(head.getPosition().x + x, head.getPosition().y + y);
}

void Snake::move_manual(const int x, const int y)
{
	this->x = x;
	this->y = y;
	if (body.size())
	{
		grow();
		body.pop_front();
	}
	else
		head.setPosition(head.getPosition().x + x, head.getPosition().y + y);
}

bool Snake::check_move(const int x, const int y)
{
	if (body.size())
	{
		int k = 0;
		for (auto i = body.rbegin(); k <= 4 && i != body.rend(); i++, ++k)
		{
			if (i->getPosition().x == head.getPosition().x + step[x] && i->getPosition().y == head.getPosition().y + step[y])//(snake_neck_coor.x == snake_head_coor.x + step[x] && snake_neck_coor.y == snake_head_coor.y + step[y])
				return false;
		}
	}
	return true;
}

bool Snake::check_move()
{
	if (body.size())
	{
		int k = 0;
		for (auto i = body.rbegin(); k <= 4 && i != body.rend(); i++, ++k)
		{
			if (i->getPosition().x == head.getPosition().x + x && i->getPosition().y == head.getPosition().y + y)
				return false;
		}
	}
	return true;
}

bool Snake::check_move_m(const int x, const int y)
{
	if (body.size())
	{
		int k = 0;
		for (auto i = body.rbegin(); k <= 4 && i != body.rend(); i++, ++k)
		{
			if (i->getPosition().x == head.getPosition().x + x && i->getPosition().y == head.getPosition().y + y)
				return false;
		}
	}
	return true;
}

std::list <sf::RectangleShape> Snake::get_body()
{
	return body;
}

sf::RectangleShape Snake::get_head()
{
	return head;
}

void Snake::set_time(const float time, const float t)
{
	if (time < 0 || t < 0)
		this->time = 0.f;
	this->time = time * t;
}

