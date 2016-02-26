#include <Wt/WApplication>
#include <Wt/WText>

#include "opval.h"
#include "FormView.h"

class OpCalcApplication : public Wt::WApplication
{
public:
    OpCalcApplication(Wt::WEnvironment const& env)
        : Wt::WApplication(env)
    {
        using namespace Wt;

        std::string title = "American Option Calculator";

        setTitle(title);

        wtTitle = new WText(root());
        wtTitle->setText(title);

        FormView * view = new FormView(root());
    }

private:
    Wt::WText *wtTitle;
};

Wt::WApplication* createApplication(Wt::WEnvironment const& env)
{
    return new OpCalcApplication(env);
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, &createApplication);;
}
