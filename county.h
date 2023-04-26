#include <string>
using namespace std;

class County {
public:
  // constructor
  County(const string &name, int ageDistribution, int educationLevel,
         int employmentStatistics, double ethnicityPercentages, int housHold,
         int income);
  string getName();
  int getAgeDistribution();
  int getEducationLevel();
  int getEmploymentStatistics();
  double EthnicityInfo();
  int getIncome();

private:
  string name;
  int ageDistribution;
  int educationLevel;
  int employmentStatistics;
  int income;
  int ethnicityPercentages;
  int householdInfo;
};
