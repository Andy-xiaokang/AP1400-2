#include "espresso_based.h"
#include "ingredient.h"

#include <ftxui/dom/elements.hpp>  // for text, hbox, window, Elements, operator|, border
#include <ftxui/screen/screen.hpp> // for Screen
#include <ftxui/screen/string.hpp> // for to_wstring
#include <map>
#include <iostream>
#include <thread>
EspressoBased::~EspressoBased()
{
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

std::vector<Ingredient *> &EspressoBased::get_ingredients() {
    return ingredients;
}

EspressoBased::EspressoBased() : ingredients({}), name(""){

}

EspressoBased::EspressoBased(const EspressoBased &esp) : name(esp.name) {
    for (auto& ptr : esp.ingredients) {
        ingredients.push_back(ptr->clone());
    }
}

void EspressoBased::operator=(const EspressoBased &esp) {
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
    name = esp.name;
    for (auto& ptr : esp.ingredients) {
        ingredients.push_back(ptr->clone());
    }
}

// the brew() function refer from https://note.sbwcwso.com/CSStudy/#/page/c%2B%2B%2Fadvanced%20programming%20course

void EspressoBased::brew()
{
    using namespace ftxui;
    std::map<std::string, Color> colors =
            {
                    {"Cinnamon", Color::Red3},
                    {"Chocolate", Color::DarkRed},
                    {"Sugar", Color::White},
                    {"Cookie", Color::Yellow},
                    {"Milk", Color::LightSalmon3Bis},
                    {"MilkFoam", Color::GrayDark},
                    {"Water", Color::Blue},
                    {"Espresso", Color::DarkGoldenrod},
            };

    std::map<std::string, int> units = {};

    int total_units = 0;
    for (const auto &i : ingredients)
    {
        units[i->get_name()] = i->get_units();
        total_units += i->get_units();
    }

    if (total_units == 0)
        throw std::invalid_argument("There is no ingredients.");

    int width = 30;                   // The progress bar width
    int cup_height = total_units + 1; // the height of the cup

    int max_progress = 100;
    int progress = 0;

    std::cout.flush();

    while (true)
    {

        Elements children;

        std::wstring progress_bar = L"";
        for (int i = 0; i < width; ++i)
        {
            if (i < (progress * width / max_progress))
                progress_bar += L"#";
            else
                progress_bar += L" ";
        }
        auto progress_text = text(L"Brewing: [" + progress_bar + L"] " + to_wstring(progress) + L"%");

        int current_height = 0;

        for (auto const &pair : units)
        {
            int height = pair.second;

            for (int j = 0; j < height; ++j)
            {
                if (current_height <= (progress - 10) * cup_height / (double)max_progress)
                {
                    if (j == 0)
                        children.push_back(text(pair.first) | hcenter | color(Color::Black) | bgcolor(colors[pair.first]));
                    else
                        children.push_back(text("") | hcenter | color(Color::Black) | bgcolor(colors[pair.first]));
                }
                else
                {
                    /* The empty space at current progress. */
                    children.push_back(text(L" ") | hcenter | color(Color::White) | bgcolor(Color::White));
                }
                current_height++;
            }
        }

        /* The space for the last line on the cup. */
        children.push_back(text(L" ") | hcenter | color(Color::White) | bgcolor(Color::White));
        std::reverse(children.begin(), children.end());

        auto document = window(text(L"Progress"), vbox({progress_text,
                                                        separator(),
                                                        vbox(children) | border})) |
                        nothing;

        auto screen = Screen::Create(Dimension::Fixed(60), Dimension::Fit(document));
        std::string reset_position = screen.ResetPosition(true);
        Render(screen, document);
        screen.Print();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        progress++;
        if (progress > max_progress)
            break;
        std::cout << reset_position;
    }
    std::cout << std::endl;
}


