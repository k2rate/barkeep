#include <iostream>

#include <barkeep.h>

int main()
{
    using namespace std::chrono_literals;
    namespace bk = barkeep;

    std::atomic<size_t> linear{0}, quad{0}, cubic{0};
    auto bars = bk::Composite({bk::ProgressBar(&linear,
                                               {
                                                   .total = 100,
                                                   .message = "Linear   ",
                                                   .speed = 0,
                                                   .style = bk::Rich,
                                                   .show = false,
                                               }),
                               bk::ProgressBar(&quad,
                                               {
                                                   .total = 5050,
                                                   .message = "Quadratic",
                                                   .speed = 0,
                                                   .style = bk::Rich,
                                                   .show = false,
                                               }),
                               bk::ProgressBar(&cubic,
                                               {
                                                   .total = 171700,
                                                   .message = "Cubic    ",
                                                   .speed = 0,
                                                   .style = bk::Rich,
                                                   .show = false,
                                               })},
                              "\n");

    bars->show();
    for (int i = 0; i < 100; i++)
    {
        std::this_thread::sleep_for(130ms);
        linear++;
        quad += linear;
        cubic += quad;
    }

    bars->done();

    return 0;
}
