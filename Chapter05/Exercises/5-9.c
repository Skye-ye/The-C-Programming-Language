static int daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day) {
  int leap;
  int *p;
  if (month < 1 || month > 12) {
    return -1;
  }

  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

  if (day < 1 || day > *(*(daytab + leap) + month)) {
    return -1;
  }

  p = *(daytab + leap) + 1;
  while (--month) {
    day += *p++;
  }

  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int leap;
  int *p;
  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

  if ((leap && yearday > 366) || (!leap && yearday > 365)) {
    *pmonth = -1;
    *pday = -1;
    return;
  }

  while (yearday > *p) {
    yearday -= *p++;
  }
  *pmonth = p - *(daytab + leap);
  *pday = yearday;
}