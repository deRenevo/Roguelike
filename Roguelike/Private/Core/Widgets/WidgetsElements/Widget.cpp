#include <Core/Widgets/WidgetsElements/Widget.h>

#include <iostream>

void Widget::OnEnter()
{
	Construction();
}

void Widget::OnExit()
{
	
}

void Widget::Tick(float DeltaTime)
{
	
}

void Widget::Draw()
{
	
}

void Widget::DoTick(float DeltaTime)
{
	if (!bIsVisible) return; // then remove to Enum class with Widget state
	Tick(DeltaTime);
}

void Widget::DoDraw()
{
	if (!bIsVisible) return; // then remove to Enum class with Widget state
	Draw();
}

/*
 * => setter and getter
*/

void Widget::SetWorldLocation(Vector2 location)
{
	if (Parent)
	{
		Bound.x = location.x - Parent->GetWorldLocation().x;
		Bound.y = location.y - Parent->GetWorldLocation().y;
	}
	else
	{
		Bound.x = location.x;
		Bound.y = location.y;
	}
}

void Widget::SetLocalLocation(Vector2 location)
{
	Bound.x = location.x;
	Bound.y = location.y;
}

void Widget::SetVisible(bool isVisible)
{
	bIsVisible = isVisible;
}

void Widget::SetSize(Vector2 size)
{
	Bound.width = size.x;
	Bound.height = size.y;
}

void Widget::SetParent(Widget* parent)
{
	Parent = parent;
}

void Widget::SetBound(Rectangle bound)
{
	std::cout << "SetBound called: x=" << bound.x
		<< " y=" << bound.y
		<< " w=" << bound.width
		<< " h=" << bound.height << std::endl;

	Bound = bound;
}

Rectangle Widget::GetLocalBound()
{
	return Bound;
}

Rectangle Widget::GetWorldBound()
{
	return Rectangle(GetWorldLocation().x, GetWorldLocation().y, Bound.width, Bound.height);
}

Widget* Widget::GetParent()
{
	return Parent;
}

Vector2 Widget::GetWorldLocation()
{
	if (Parent)
	{
		return Vector2(
			Parent->GetWorldLocation().x + Bound.x,
			Parent->GetWorldLocation().y + Bound.y
		);
	}
	return Vector2(Bound.x, Bound.y);
}

Vector2 Widget::GetLocalLocation()
{
	return Vector2(Bound.x, Bound.y);
}

Vector2 Widget::GetSize()
{
	return Vector2(Bound.width, Bound.height);
}

bool Widget::GetVisible()
{
	return bIsVisible;
}
