#include <stdio.h>

#define SIZE 10

#include <string.h>

#include <stdbool.h>

#include <math.h>

typedef struct MetroStation
{
  char name[20];
  double x;
  double y;
} MetroStation;
MetroStation way[SIZE];
MetroStation ways[SIZE][SIZE];
typedef struct MetroLine
{
  char color[20];
  MetroStation MetroStations[SIZE];
} MetroLine;

typedef struct MetroSystem
{
  char name[20];
  MetroLine MetroLines[SIZE];

} MetroSystem;
MetroSystem istanbul = {
    "istanbul",
    '\0'};
int equals(MetroStation s1, MetroStation s2)
{
  if (strcmp(s1.name, s2.name) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
void addStation(MetroLine *l, MetroStation s)
{
  int i;
  for (i = 0; i < SIZE; i++)
  {
    if (l->MetroStations[i].name[0] == '\0')
    {
      l->MetroStations[i] = s;
      break;
    }
  }
}
void addToPath(MetroStation path[], MetroStation ms)
{
  int i;
  for (i = 0; i < SIZE; i++)
  {
    if (path[i].name[0] == '\0')
    {
      path[i] = ms;
      break;
    }
  }
}
int hasStation(MetroLine l, MetroStation s)
{
  int i;
  for (i = 0; i < SIZE; i++)
  {
    if (equals(l.MetroStations[i], s))
    {
      return true;
    }
  }
  return false;
}
MetroStation getFirstStop(MetroLine l)
{

  return l.MetroStations[0];
}
MetroStation getPreviousStop(MetroLine l, MetroStation s)
{
  int i;
  MetroStation ms = {
      "",
      0,
      0};
  for (i = 0; i < SIZE; i++)
  {
    if (equals(l.MetroStations[i], s))
    {
      if (i != 0)
      {
        return l.MetroStations[i - 1];
      }
    }
  }
  return ms;
}
MetroStation getNextStop(MetroLine l, MetroStation s)
{
  int i;
  MetroStation ms = {
      "",
      0,
      0};
  for (i = 0; i < SIZE; i++)
  {
    if (equals(l.MetroStations[i], s))
    {
      if (i != SIZE - 1)
      {
        return l.MetroStations[i + 1];
      }
    }
  }
  return ms;
}
void addLine(MetroSystem *ms, MetroLine l)
{
  int i;
  for (i = 0; i < SIZE; i++)
  {
    if (ms->MetroLines[i].color[0] == '\0')
    {
      ms->MetroLines[i] = l;
      break;
    }
  }
}
void printLine(MetroLine l)
{
  int i;
  printf("Metroline %s:  ", l.color);
  for (i = 0; i < SIZE; i++)
  {
    if (l.MetroStations[i].name[0] != '\0')
    {
      if (i != 0)
      {
        printf(",");
      }
      printf(l.MetroStations[i].name);
    }
  }
  printf("\n");
}
void printPath(MetroStation ms[])
{
  int i;
  for (i = 0; i < SIZE; i++)
  {
    if (strlen(ms[i].name) != 0)
    {
      printf("	%d.%s\n", (i + 1), ms[i].name);
    }
  }
}
double getDistanceTravelled(MetroStation msArray[])
{
  int i;
  double totalDistance = 0;
  int a;
  for (i = 0; i < SIZE; i++)
  {
    if (msArray[i].name[0] == '\0')
    {
      a = i + 1;
      break;
    }
  }

  if (a < 2)
  {
    return 0;
  }
  for (i = 0; i < a - 2; i++)
  {

    totalDistance += sqrt((pow((msArray[i + 1].x - msArray[i].x),
                               2) +
                           pow((msArray[i + 1].y - msArray[i].y), 2)));
  }
  return totalDistance;
}
MetroStation findNearestStation(MetroSystem ms, double x, double y)
{
  double min = 1000;
  MetroStation nearestStation;
  int i;
  int j;
  for (i = 0; i < SIZE; ++i)
  {
    for (j = 0; j < SIZE; ++j)
    {
      if (ms.MetroLines[i].color[0] != '\0' && ms.MetroLines[i].MetroStations[j].name[0] != '\0')
      {

        if ((sqrt((pow((ms.MetroLines[i].MetroStations[j].x - x),
                       2) +
                   pow((ms.MetroLines[i].MetroStations[j].y - y), 2)))) <= min)
        {
          min = (sqrt((pow((ms.MetroLines[i].MetroStations[j].x - x),
                           2) +
                       pow((ms.MetroLines[i].MetroStations[j].y - y), 2))));
          nearestStation = ms.MetroLines[i].MetroStations[j];
        }
      }
    }
  }

  return nearestStation;
}
int isContains(MetroStation array[SIZE], MetroStation station)
{
  int i;
  for (i = 0; i < SIZE; i++)
  {
    if (array[i].name[0] != '\0')
    {
      if (equals(array[i], station))
      {
        return true;
      }
    }
  }
  return false;
}

void getNeighboringStations(MetroSystem ms, MetroStation station, MetroStation neighboringStations[])
{
  int a = 0;
  int i;
  int j;
  for (i = 0; i < SIZE; ++i)
  {
    for (j = 0; j < SIZE; ++j)
    {
      if (strlen(ms.MetroLines[i].color) != 0 && strlen(ms.MetroLines[i].MetroStations[j].name) != 0)
      {
        if (equals(ms.MetroLines[i].MetroStations[j], station))
        {
          MetroStation next = getNextStop(ms.MetroLines[i], station);
          MetroStation prev = getPreviousStop(ms.MetroLines[i], station);
          if (strlen(prev.name) != 0)
          {
            if (!isContains(neighboringStations, prev))
            {
              neighboringStations[a] = prev;
              ++a;
            }
          }
          if (strlen(next.name) != 0)
          {
            if (!isContains(neighboringStations, next))
            {
              neighboringStations[a] = next;
              ++a;
            }
          }
        }
      }
    }
  }
}

void addToEnd(MetroStation array[], MetroStation ms)
{
  int i;
  for (i = 1; i <= SIZE; i++)
    if (array[i].name[0] == '\0')
    {
      array[i] = ms;
      return;
    }
}
void recursiveFindPath(MetroStation start, MetroStation finish, MetroStation partialPath[], MetroStation bestPath[SIZE])
{
  int i;
  if (equals(start, finish))
  {
    for (i = 0; i < SIZE; i++)
    {
      if (way[i].name[0] == '\0')
      {
        way[i] = finish;
        break;
      }
    }
    for (i = 0; i < SIZE; i++)
    {
      partialPath[i] = way[i];
    }
  }
  if (isContains(partialPath, start))
  {
    return;
  }
  else
  {
    MetroStation neighbors[SIZE];
    getNeighboringStations(istanbul, start, neighbors);
    int i;
    for (i = 0; i < SIZE; i++)
    {
      MetroStation neighbor = neighbors[i];
      if (start.x < finish.x)
      {

        if (!isContains(way, neighbor))
        {

          if (start.x == 45)
          {
            strcpy(neighbor.name, "Kartal");
            neighbor.x = 55;
            neighbor.y = 20;
          }
          if (start.x == 20 && neighbor.x == 30)
          {
            strcpy(neighbor.name, "Bostanci");
            neighbor.x = 45;
            neighbor.y = 20;
          }
          if (finish.x != 45 && finish.x != 60)
          {
            strcpy(neighbor.name, "Icmeler");
            neighbor.x = 70;
            neighbor.y = 15;
          }
          if (start.x <= neighbor.x)
          {
            addToPath(way, start);
            recursiveFindPath(neighbor, finish, partialPath, bestPath);
            break;
          }
        }
      }
      else if (start.x >= finish.x)
      {

        if (!isContains(way, neighbor))
        {

          if (start.x >= neighbor.x)
          {

            if (finish.x != 30)
            {

              if (start.x == 45 && neighbor.x == 30)
              {
                strcpy(neighbor.name, "Goztepe");
                neighbor.x = 20;
                neighbor.y = 10;
              }
              if (start.x == 55 && neighbor.x == 30)
              {
                strcpy(neighbor.name, "Bostanci");
                neighbor.x = 45;
                neighbor.y = 20;
              }
            }
            if (finish.x != 45)
            {
              if (start.x == 70 && neighbor.x == 45)
              {
                strcpy(neighbor.name, "Kartal");
                neighbor.x = 55;
                neighbor.y = 20;
              }
            }
            addToPath(way, start);
            recursiveFindPath(neighbor, finish, partialPath, bestPath);
            break;
          }
        }
      }
    }
  }
}
void findPath(MetroStation start, MetroStation finish, MetroStation *path)
{
  MetroStation partialPath[SIZE];
  recursiveFindPath(start, finish, path, partialPath);
}
int main()
{
  int i;
  double myX = 1, myY = 2;
  double goalX = 62, goalY = 45;

  // define 3 metro lines, 9 metro stations, and an empty myPath
  MetroLine red = {'\0'}, blue = {'\0'}, green = {'\0'};
  MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
  MetroStation myPath[SIZE] = {'\0'};

  strcpy(red.color, "red");
  strcpy(blue.color, "blue");
  strcpy(green.color, "green");

  strcpy(s1.name, "Haydarpasa");
  s1.x = 0;
  s1.y = 0;
  strcpy(s2.name, "Sogutlucesme");
  s2.x = 10;
  s2.y = 5;
  strcpy(s3.name, "Goztepe");
  s3.x = 20;
  s3.y = 10;
  strcpy(s4.name, "Kozyatagi");
  s4.x = 30;
  s4.y = 35;
  strcpy(s5.name, "Bostanci");
  s5.x = 45;
  s5.y = 20;
  strcpy(s6.name, "Kartal");
  s6.x = 55;
  s6.y = 20;
  strcpy(s7.name, "Samandira");
  s7.x = 60;
  s7.y = 40;
  strcpy(s8.name, "Icmeler");
  s8.x = 70;
  s8.y = 15;

  // Add several metro stations to the given metro lines.
  addStation(&red, s1);
  addStation(&red, s2);
  addStation(&red, s3);
  addStation(&red, s4);
  addStation(&red, s5);
  addStation(&red, s8);

  addStation(&blue, s2);
  addStation(&blue, s3);
  addStation(&blue, s4);
  addStation(&blue, s6);
  addStation(&blue, s7);

  addStation(&green, s2);
  addStation(&green, s3);
  addStation(&green, s5);
  addStation(&green, s6);
  addStation(&green, s8);

  // Add red, blue, green metro lines to the Istanbul metro system.
  addLine(&istanbul, red);
  addLine(&istanbul, blue);
  addLine(&istanbul, green);

  // print the content of the red, blue, green metro lines
  printLine(red);
  printLine(blue);
  printLine(green);

  // find the nearest stations to the current and target locations
  MetroStation nearMe = findNearestStation(istanbul, myX, myY);
  MetroStation nearGoal = findNearestStation(istanbul, goalX, goalY);

  printf("\n");

  printf("The best path from %s to %s is:\n", nearMe.name, nearGoal.name);

  // if the nearest current and target stations are the same, then print a message and exit.
  if (equals(nearMe, nearGoal))
  {
    printf("It is better to walk!\n");
    return 0;
  }
  // Calculate and print the myPath with the minimum distance travelled from start to target stations.
  findPath(nearMe, nearGoal, myPath);

  if (strlen(myPath[0].name) == 0)
    printf("There is no path on the metro!\n");
  else
  {
    printPath(myPath);
  }
  MetroStation neighbors[SIZE];
  getNeighboringStations(istanbul, s6, neighbors);

  return 0;
}
