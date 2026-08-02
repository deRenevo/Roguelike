#include <Core/Widgets/WidgetsElements/Container.h>

#include <iostream>
#include <algorithm>

void WContainer::OnExit()
{
    for (auto& child : Children)
    {       
        child->OnExit();
    }
    Children.clear();
}

void WContainer::Tick(float DeltaTime)
{
    WWidget::Tick(DeltaTime);

    for (auto& child : Children)
    {
        //std::cout << "Tick | child:";
        child->DoTick(DeltaTime);
    }
}

void WContainer::Draw()
{
    WWidget::Draw();
    for (auto& child : Children)
    {
        child->DoDraw();
    }
}

void WContainer::Construction()
{
        
}

void WContainer::OnChildAdded(WWidget* widget)
{
}

/*
 * => getter and setter
*/

void WContainer::AddChild(std::unique_ptr<WWidget> widget)
{
    if (!widget) return;
    widget->SetParent(this);
    widget->OnEnter();
    auto* ptr = widget.get();
    Children.push_back(std::move(widget));
    OnChildAdded(ptr);
}


void WContainer::RemoveChild(WWidget* widget)
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

void WContainer::ClearChildren()
{
    for (auto& child : Children)
    {
        child->OnExit();
    }
    Children.clear();
}
