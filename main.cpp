#include <Wt/WApplication>
#include <Wt/WText>

#include "FormView.h"

namespace opcalc {

class Application : public Wt::WApplication
{
public:
    Application(Wt::WEnvironment const& env)
        : Wt::WApplication(env)
    {
        using namespace Wt;

        std::string title = "American Option Calculator";

        setTitle(title);

        wtTitle = new WText(root());
        wtTitle->setText(title);

        new FormView(root());
    }

private:
    Wt::WText *wtTitle;
};

}

namespace {
    Wt::WApplication* createApplication(Wt::WEnvironment const& env)
    {
        return new opcalc::Application(env);
    }
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, &createApplication);
}
