static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* Gets day of year from month & day
 *
 * @param year
 * @param month
 * @param day
 * @return the day of year for valid input
 *         -1 for other
 */
int Day_Of_Year(int year, int month, int day) {
  int i, leap;

  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

  if (month < 1 || month > 12) {
    return -1;
  }
  if (day < 1 || day > daytab[leap][month]) {
    return -1;
  }
  for (i = 1; i < month; i++) {
    day += daytab[leap][i];
  }
  return day;
}

/* Gets mounth and day from day of year
 *
 * @param year
 * @param day_of_year
 * @param pmonth[out]
 * @param pday[out]
 */
void Get_Month_Day(int year, int day_of_year, int *pmonth, int *pday) {
  int i, leap;

  if (year < 1) {
    *pmonth = -1;
    *pday = -1;
    return;
  }
  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; i <= 12 && day_of_year > daytab[leap][i]; i++) {
    day_of_year -= daytab[leap][i];
  }
  if (i > 12 && day_of_year > daytab[leap][12]) {
    *pmonth = -1;
    *pday = -1;
  } else {
    *pmonth = i;
    *pday = day_of_year;
  }
}
