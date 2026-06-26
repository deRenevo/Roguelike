#include <Core/Widgets/WidgetsElements/Container.h>

class CanvasPanel : public Container
{

protected:
	virtual void Construction() override;
	virtual void Draw() override;
};