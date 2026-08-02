#include <Core/Widgets/WidgetsElements/Container.h>

class WCanvasPanel : public WContainer
{

protected:
	virtual void Construction() override;
	virtual void Draw() override;

public:
	virtual Vector2 GetSize() override;
};