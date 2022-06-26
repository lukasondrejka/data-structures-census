
#include <string>
#include "structures/heap_monitor.h"
#include "cli/cli.h"
#include "census/census.h"
#include "census/territorial_unit/filters.h"
#include "census/territorial_unit/selection_criterions.h"
#include "implementation/composite_filter.h"
#include "implementation/selector.h"
#include "implementation/sorting/shell_sort.h"
#include "implementation/sorting/quick_sort.h"
#include "implementation/smart_ptr.h"

Census* census;

void app();

int main(){
    initHeapMonitor();
    initCLI();

    census = new Census();
    cout << "Načítavanie" << endl;
    census->load();
    cout << "Načítané" << endl << endl;

    app();

    delete census;
    return 0;
}

void app()
{
    auto fiAnd = new Filter_AND<TerritorialUnit*>();
    fiAnd->registerFilter(new FilterPopulation(1500, 1800));
    fiAnd->registerFilter(new FilterEducationCount(VYSOKOSKOLSKE, 100, 500));

    auto result = SharedPtr<Container<TerritorialUnit*>>(
        Selector<TerritorialUnit*>(fiAnd).select(*census->units(MUNICIPALITIES)));

    ShellSort<TerritorialUnit*, std::string>(new CriterionTitle())(*result);

    for (auto unit : *result)
        cout << *unit << endl;

}
