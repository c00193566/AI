#include "KinematicMethods.h"

float KinematicMethods::getOrientation(float CurrentOrientation, Vector2f Velocity, CalculationMethods VectorModifiers)
{
	float rotation = CurrentOrientation;

	if (VectorModifiers.Length(Velocity) > 0)
	{
		rotation = atan2f(Velocity.x, -Velocity.y);

		rotation = VectorModifiers.RadsToDegs(rotation);
	}

	return rotation;
}

void KinematicMethods::Seek(Character* Input, Character* Target, CalculationMethods VectorModifiers)
{
	Input->Attributes.Velocity = Target->Attributes.Position - Input->Attributes.Position;

	Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

	if (Input->InFormation)
	{
		Input->Attributes.Velocity *= Input->ModifiedSpeed;
	}
	else
	{
		Input->Attributes.Velocity *= Input->MaxSpeed;
	}

	Input->Attributes.Orientation = getOrientation(Input->Attributes.Orientation, Input->Attributes.Velocity, VectorModifiers);

	Input->CharacterSprite.setRotation(Input->Attributes.Orientation);
}

void KinematicMethods::Seek(Character* Input, Vector2f Target, CalculationMethods VectorModifiers)
{
	Input->Attributes.Velocity = Target - Input->Attributes.Position;

	Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

	if (Input->InFormation)
	{
		Input->Attributes.Velocity *= Input->ModifiedSpeed;
	}
	else
	{
		Input->Attributes.Velocity *= Input->MaxSpeed;
	}

	Input->Attributes.Orientation = getOrientation(Input->Attributes.Orientation, Input->Attributes.Velocity, VectorModifiers);

	Input->CharacterSprite.setRotation(Input->Attributes.Orientation);
}

void KinematicMethods::Pursuit(Character* Input, Character* Target, CalculationMethods Calc)
{
	float TimePerdiction = 0.0f;
	float MaxTimePerdiction = 5.0f;

	Vector2f Dir = Target->Attributes.Position - Input->Attributes.Position;
	float Distance = Calc.Length(Dir);

	float Speed = Calc.Length(Input->Attributes.Velocity);

	if (Speed <= Distance / MaxTimePerdiction)
	{
		TimePerdiction = MaxTimePerdiction;
	}
	else
	{
		TimePerdiction = Distance / Speed;
	}

	Vector2f TargetPrediction = Target->Attributes.Position + Target->Attributes.Velocity * TimePerdiction;

	Seek(Input, TargetPrediction, Calc);
}

void KinematicMethods::Flee(Character* Input, Character* Target, CalculationMethods VectorModifiers)
{
	Input->Attributes.Velocity = Input->Attributes.Position - Target->Attributes.Position;

	Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

	Input->Attributes.Velocity *= Input->MaxSpeed;

	Input->Attributes.Orientation = getOrientation(Input->Attributes.Orientation, Input->Attributes.Velocity, VectorModifiers);

	Input->CharacterSprite.setRotation(Input->Attributes.Orientation);
}

void KinematicMethods::Arrive(Character* Input, Character* Target, CalculationMethods VectorModifiers)
{
	float TimeToTarget = 0.01f;

	Input->Attributes.Velocity = Target->Attributes.Position - Input->Attributes.Position;

	/*if (VectorModifiers.Length(Input->Attributes.Velocity) > Target->Radius)
	{
		Input->Behaviour = MovementBehaviour::Seek;
	}*/

	Input->Attributes.Velocity *= TimeToTarget;

	if (Input->InFormation)
	{
		if (VectorModifiers.Length(Input->Attributes.Velocity) > Input->ModifiedSpeed)
		{
			Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

			Input->Attributes.Velocity *= Input->ModifiedSpeed;
		}
	}
	else
	{
		if (VectorModifiers.Length(Input->Attributes.Velocity) > Input->MaxSpeed)
		{
			Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

			Input->Attributes.Velocity *= Input->MaxSpeed;
		}
	}

	Input->Attributes.Orientation = getOrientation(Input->Attributes.Orientation, Input->Attributes.Velocity, VectorModifiers);

	Input->CharacterSprite.setRotation(Input->Attributes.Orientation);
}

void KinematicMethods::Arrive(Character * Input, Vector2f Target, CalculationMethods VectorModifiers)
{
	float TimeToTarget = 0.01f;

	Input->Attributes.Velocity = Target - Input->Attributes.Position;

	/*if (VectorModifiers.Length(Input->Attributes.Velocity) > Target->Radius)
	{
	Input->Behaviour = MovementBehaviour::Seek;
	}*/

	Input->Attributes.Velocity *= TimeToTarget;

	if (Input->InFormation)
	{
		if (VectorModifiers.Length(Input->Attributes.Velocity) > Input->ModifiedSpeed)
		{
			Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

			Input->Attributes.Velocity *= Input->ModifiedSpeed;
		}
	}
	else
	{
		if (VectorModifiers.Length(Input->Attributes.Velocity) > Input->MaxSpeed)
		{
			Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

			Input->Attributes.Velocity *= Input->MaxSpeed;
		}
	}

	Input->Attributes.Orientation = getOrientation(Input->Attributes.Orientation, Input->Attributes.Velocity, VectorModifiers);

	Input->CharacterSprite.setRotation(Input->Attributes.Orientation);
}

void KinematicMethods::Wander(Character* Input, WanderComponents* Target, CalculationMethods Calc)
{
	Target->LastUpdate += 1.0f / 60.0f;

	if (Target->LastUpdate >= 0.35f)
	{
		Target->LastUpdate = 0.0f;
	}

	if (Target->LastUpdate == 0.0f || Input->Attributes.Position == Target->Target)
	{
		Vector2f Dir = Calc.Normalize(Input->Attributes.Velocity);
		Vector2f Point = Dir * Target->Distance;
		Point += Input->Attributes.Position;

		float angle = (static_cast<float>(rand() / (RAND_MAX / 361.0f))) * PI / 180;
		angle *= Calc.RandomClamp();

		float x = Target->Radius * sin(angle) + Point.x;
		float y = Target->Radius * cos(angle) + Point.y;

		Point = Vector2f(x, y);

		Target->Target = Point;
	}

	Seek(Input, Target->Target, Calc);
}