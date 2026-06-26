#include <Core/Widgets/WidgetsElements/Container.h>

#include <iostream>

void Container::OnExit()
{
    for (auto& child : Children)
    {
        child->OnExit();
    }
    Children.clear();
}

void Container::Tick(float DeltaTime)
{
    Widget::Tick(DeltaTime);

    for (auto& child : Children)
    {
        //std::cout << "Tick | child:";
        child->DoTick(DeltaTime);
    }
}

void Container::Draw()
{
    Widget::Draw();
    for (auto& child : Children)
    {
        child->DoDraw();
    }
}

void Container::Construction()
{
        
}

void Container::OnChildAdded(Widget* widget)
{
}

/*
 * => getter and setter
*/

void Container::AddChild(std::unique_ptr<Widget> widget)
{
    if (!widget) return;
    widget->SetParent(this);
    widget->OnEnter();
    auto* ptr = widget.get();
    Children.push_back(std::move(widget));
    OnChildAdded(ptr);
}


void Container::RemoveChild(Widget* widget)
{
    if (!widget) return;

    auto ptr = std::find_if(Children.begin(), Children.end(),
        [widget](const auto& c) { return c.get() == widget; });

    if (ptr != Children.end())
    {
        (*ptr)->OnExit();
        Children.erase(ptr);
    }
}

void Container::ClearChildren()
{
    for (auto& child : Children)
    {
        child->OnExit();
    }
    Children.clear();
}
