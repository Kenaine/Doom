#include "RayCast.h"
#include <vector>
#include <tuple>
#include <cmath>
#include <limits>
#include <thread>



RayCast::RayCast(Player& p, std::vector<sf::VertexArray> object) : 
	player(p), objects(object)
{
	distances.reserve(vertexCount);
	fan = sf::VertexArray(sf::PrimitiveType::TriangleFan, vertexCount + 2);
}

//Cast rays and update fan vertices
void RayCast::update()
{
	//Get player position and 
	distances.clear();
	sf::Vector2f playerPos = player.getSprite().getPosition();
	sf::Angle playerRot = player.getSprite().getRotation();

	//initialize  and last vertex of the fan to player position
	fan[0].position = playerPos;
	fan[vertexCount + 1].position = playerPos;

	//Loop through the fov and cast rays and return closest intersection point
	float fovRad = player.getFov().asRadians();
	float startAngle = playerRot.asRadians() - (fovRad / 2.f);
	float endAngle = playerRot.asRadians() + (fovRad / 2.f);

	float steps = fovRad / vertexCount;

	for (int i = 0; i <= vertexCount; i++)
	{
		//find second point of the ray based on angle and max distance
		float currentAngle = startAngle + (steps * i);
		float xPos = playerPos.x + cos(currentAngle) * maxDistance;
		float yPos = playerPos.y + sin(currentAngle) * maxDistance;

		sf::Vector2f rayEndPoint = sf::Vector2f(xPos, yPos);

		float distance = 0.f;

		//check if ray intersects with any objects and get closest intersection point
		sf::Vector2f point = findIntersectionPoint(playerPos, rayEndPoint, distance);

		//Set fan vertices based on intersection points
		fan[i + 1].position = point;
		fan[i + 1].color = sf::Color::Blue; 

		distances.push_back(distance);
	}

}

sf::Vector2f RayCast::findIntersectionPoint(sf::Vector2f rayStart, sf::Vector2f rayEnd, float& closestDistance)
{
	float a1, b1, c1; //ray line coefficients

	//get line coefficients for the ray
	twoPointToLine(rayStart, rayEnd, a1, b1, c1);
	sf::Vector2f closestPoint = rayEnd;
	closestDistance = maxDistance;

	//loop through all objects to check for intersection
	for (auto object : objects)
	{
		//loop through each line segment in the object
		for (int i = 0; i < object.getVertexCount() - 1; i++)
		{
			sf::Vector2f intersectionPoint;
			float a2, b2, c2; //wall line coefficients
			//get line coefficients for the wall segment
			if (i == object.getVertexCount() - 1)
				twoPointToLine(object[i].position, object[0].position, a2, b2, c2);
			else
				twoPointToLine(object[i].position, object[i + 1].position, a2, b2, c2);
			//check intersection
			float line1[3] = { a1, b1, c1 }, line2[3] = { a2, b2, c2 };
			if (checkIntersection(line1, line2, intersectionPoint))
			{
				//check if intersection point is infront of the ray start point
				//if the sum between the distance between ray start and intersection point and intersection and ray end is equal
				//to the distance between ray start and ray end, then the intersection point is infront of the ray start point
				//calculate distance
				float distanceToIntersection = sqrt(pow(intersectionPoint.x - rayStart.x, 2) + pow(intersectionPoint.y - rayStart.y, 2));
				float distanceToEnd = sqrt(pow(rayEnd.x - intersectionPoint.x, 2) + pow(rayEnd.y - intersectionPoint.y, 2));

				float totalDistance = distanceToIntersection + distanceToEnd;

				float difference = std::abs(maxDistance - totalDistance);
				
				if (std::round(difference) == 0 && 
					distanceToIntersection < closestDistance)
				{
					closestDistance = distanceToIntersection;
					closestPoint = intersectionPoint;
				}
			}
		}
	}


	return closestPoint;
}

void RayCast::twoPointToLine(sf::Vector2f point1, sf::Vector2f point2, float& a, float& b, float& c)
{
	//if vertical line
	if (point1.x == point2.x)
	{
		a = 1.f;
		b = 0.f;
		c = -point1.x;
	}
	else if (point1.y == point2.y) //if horizontal line
	{
		a = 0.f;
		b = 1.f;
		c = -point1.y;
	}
	else //anything else
	{
		//calculate slope m ((y2 - y1) / (x2 - x1)	
		float m = (point2.y - point1.y) / (point2.x - point1.x);
		//multiply m out y - y1 = mx - mx1
		float mx1 = m * -point1.x;
		//add y1 to both sides y = mx + (- mx1 + y1)
		c = mx1 + point1.y;
		//rearrange to general form ax + by + c = 0
		a = m;
		b = -1.f;
	}
	
}

//check intersection between two lines in general form ax + by + c = 0
//line1[0] = a, line1[1] = b, line1[2] = c
bool RayCast::checkIntersection(float line1[3], float line2[3], sf::Vector2f& intersectionPoint)
{
	//if slope is the same, lines are parallel
	if (line1[0] == line2[0])
		return false;

	//calculate intersection point
	intersectionPoint.x = (line1[1] * line2[2] - line2[1] * line1[2]) / (line1[0] * line2[1] - line2[0] * line1[1]);
	intersectionPoint.y = (line2[0] * line1[2] - line1[0] * line2[2]) / (line1[0] * line2[1] - line2[0] * line1[1]);

	return true;
}

void RayCast::iterateRay(int start, int end, float startAngle, float steps, sf::Vector2f playerPos)
{
	for (int i = start; i <= end; i++)
	{
		//find second point of the ray based on angle and max distance
		float currentAngle = startAngle + (steps * i);
		float xPos = playerPos.x + cos(currentAngle) * maxDistance;
		float yPos = playerPos.y + sin(currentAngle) * maxDistance;

		sf::Vector2f rayEndPoint = sf::Vector2f(xPos, yPos);

		float distance = 0.f;

		//check if ray intersects with any objects and get closest intersection point
		sf::Vector2f point = findIntersectionPoint(playerPos, rayEndPoint, distance);

		//Set fan vertices based on intersection points
		fan[i + 1].position = point;
		fan[i + 1].color = sf::Color::Blue;

		distances.push_back(distance);
	}
}