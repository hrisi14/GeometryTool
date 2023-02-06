#include <iostream>
#include <string>
#include<sstream>


const int MAX_SIZE = 500;
const int SIZE = 10;

bool isEqualAbs(double a, double b)
{
    double ep = 10e-9;
    if ((a - b) < ep && (a - b) > -ep)
    {
        return true;
    }
    return false;
}
void swap(int& a, int& b)
{
    int temp = b;
    b = a;
    a = temp;
}
bool isAValidSymbol(char symbol)
{
    return ((symbol>='0'&& symbol<='9')|| (symbol>='a' && symbol<='z') || (symbol>='A' && symbol<='Z') || (symbol=='_'));
}
void copyStrings(char* source, char* destination)
{
    while (*source)
    {
        *destination = *source;
        source++;
        destination++;
    }
    *destination = '\0';
}
bool validName(char* name)
{
    while (*name)
    {
        if (!isAValidSymbol(*name))
        {
            return false;
        }
        name++;
    }
    return true;
}
bool compareStrings(char* answer, char* pattern)
{
    while (*answer && *pattern)
    {
        if (*answer != *pattern)
        {
            return false;
        }
        answer++;
        pattern++;
    }
    return (*answer == '\0' && *pattern == '\0');
}
bool pointLiesOnTheLine(double a, double b, double c, double x, double y)
{
    double line = a * x + b * y + c;
    return (isEqualAbs(line, 0));
}
bool pointLiesOnTheParabola(double a, double b, double c, double x, double y)
{
    double f = a * x * x + b * x + c;
    return (isEqualAbs(f, y));
}
bool parallelLines(double a, double b, double c, double a1, double b1, double c1)
{   
    if (b != 0 && b1 != 0)
    {
        double k = -a / b;
        double k1 = -a1 / b1;
        return (isEqualAbs(k, k1));
    }
    else if (b1 == 0 && b == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void parallelLine(double a, double b, double c, double xP, double yP, double& a1, double& b1, double& c1)
{    
    if (b != 0)
    {
        double k = -a / b;      //gets the slope coefficient of the given line

       //the parallel line has the equation:  a1*x + b1*y + c1 = 0
        a1 = k;
        c1 = yP - a1 * xP;
        b1 = 1;
    }
    else if (b == 0)
    {
        b1 = 0;
        a1 = 1;
        c1 = -xP;
    }
}
void perpendicularLine(double a, double b, double c, double xp, double yp, double& a1, double& b1, double& c1)
{   
    if (b != 0)
    {
        double k = -a / b;             //gets the slope coefficient of the given line
                                       //the parallel line has the equation:  a1x + b1y + c1 = 0:
        a1 = -1/k;                //two lines (i.e. p1 and p2) are perpendicular <=> k1*k2 = -1
        c1 = round(yp - a1 * xp);
        b1 = -1;
    }
    else if (b == 0)
    {
        a1 = 0;
        b1 = 1;
        c1 = yp;
    }
}
void findIntersectionPointOfLines(double a, double b, double c, double a1, double b1, double c1, double& x, double& y, bool& matching, bool& parallel)
{
    matching = parallel = false;
    if (isEqualAbs(a, a1) && isEqualAbs(b, b1) && isEqualAbs(c, c1))  //Checks if the two lines are actually the same one
    {       
        matching = true;
    }
    else if (parallelLines(a, b, c, a1, b1, c1) && !(isEqualAbs(a, a1) || isEqualAbs(b, b1) || isEqualAbs(c, c1))) //Checks whether the two lines are parallel (have no intersection points)
    {       
        parallel = true;
  }
    else  if(b1!=0 && b!=0)                      //General case - finds the intersection point
    {
        double k = -a / b;                       //Finds the coefficient of the two lines according to their decartian equations     
        double k1 = -a1 / b1;
        double n = -c / b;
        double n1 = -c1 / b1;
        x = (n1 - n) / (k - k1);
        y = k * x + n;
    }
    else if (b == 0 && b1 != 0)
    {
        double k1 = -a1 / b1;
        double n1 = -c1 / b1;
        x = (-c-b*n1) / (a+b*k1);
        y = k1 * x + n1;
    }
    else if (b1 == 0 && b != 0)
    {
        double k = -a / b;
        double n = -c / b;
        x = (-c1-b1*n) / (a1 + b1*k);
        y = k * x + n;
    }
}
void findEquationOfALineByTwoPoints(double x1, double y1, double x2, double y2, double& a, double& b, double& c)
{
    a = y2 - y1;
    b = x1 - x2;
    c = x2 * y1 - x1 * y2;
}
double findDistanceBetweenTwoPoints(double xA, double yA, double xB, double yB)
{
    return (sqrt((xA-xB)*(xA-xB) + (yA - yB)*(yA-yB)));
}
bool suchTriangleExists(double xA, double yA, double xB, double yB, double xC, double yC)
{
    double a, b, c;
    findEquationOfALineByTwoPoints(xA, yA, xB, yB, a, b, c);
    double a1, b1, c1;
    findEquationOfALineByTwoPoints(xA, yA, xC, yC, a1, b1, c1);
    if (isEqualAbs(a, a1) && isEqualAbs(b, b1) && isEqualAbs(c, c1))  //The three points lay on the same line
    {
        return false;
    }
    double sideA = findDistanceBetweenTwoPoints(xC, yC, xB, yB);
    double sideB = findDistanceBetweenTwoPoints(xA, yA, xC, yC);
    double sideC = findDistanceBetweenTwoPoints(xA, yA, xB, yB);
    return (sideA < sideB + sideC && sideB < sideA+sideC && sideC < sideA + sideB);
}
void getEquationsOfTheSidesOfATriangle(double xA, double yA, double xB, double yB, double xC, double yC, double& aAB, double& bAB, double& cAB, double& aBC, double& bBC, double& cBC, double& aAC, double& bAC, double& cAC)
{
    if (suchTriangleExists(xA, yA, xB, yB, xC, yC))
    {
        findEquationOfALineByTwoPoints(xA, yA, xB, yB, aAB, bAB, cAB);
        findEquationOfALineByTwoPoints(xC, yC, xB, yB, aBC, bBC, cBC);
        findEquationOfALineByTwoPoints(xA, yA, xC, yC, aAC, bAC, cAC);
    }
}
void findMediansOfATriangle(double xA, double yA, double xB, double yB, double xC, double yC, double& aMAB, double& bMAB, double& cMAB, double& aMBC, double& bMBC, double& cMBC, double& aMAC, double& bMAC, double& cMAC)
{
    if (suchTriangleExists(xA, yA, xB, yB, xC, yC))
    {
        double xMedianAB = (xA + xB) / 2;
        double yMedianAB = (yA + yB) / 2;
        findEquationOfALineByTwoPoints(xC, yC, xMedianAB, yMedianAB, aMAB, bMAB, cMAB); //Median of side AB

        double xMedianBC = (xB + xC) / 2;
        double yMedianBC = (yB + yC) / 2;
        findEquationOfALineByTwoPoints(xA, yA, xMedianBC, yMedianBC, aMBC, bMBC, cMBC); //Median of side BC

        double xMedianAC = (xA + xC) / 2;
        double yMedianAC = (yA + yC) / 2;
        findEquationOfALineByTwoPoints(xB, yB, xMedianAC, yMedianAC, aMAC, bMAC, cMAC); //Median of side AC
    }
}
 
void getEquationOfHeightThroughAPoint(double a, double b, double c, double x, double y, double& aH, double& bH, double& cH)
{
    if (a != 0)
    {
        aH = b / a;
        bH = -1;
        cH = y - aH * x;
    }
    else if (a == 0)
    {
        aH = 1;
        bH = 0;
        cH = -x;
    }
}
void findHeightsOfATriangle(double xA, double yA, double xB, double yB, double xC, double yC, double& aHAB, double& bHAB, double& cHAB, double& aHBC, double& bHBC, double& cHBC, double& aHAC, double& bHAC, double& cHAC)
{
    double aAB, bAB, cAB, aBC, bBC, cBC, aAC, bAC, cAC;
    getEquationsOfTheSidesOfATriangle(xA, yA, xB, yB, xC, yC, aAB, bAB, cAB, aBC, bBC, cBC, aAC, bAC, cAC);

    getEquationOfHeightThroughAPoint(aAB, bAB, cAB, xC, yC, aHAB, bHAB, cHAB); // Height hAB (through vertex C towards side AB)
    getEquationOfHeightThroughAPoint(aBC, bBC, cBC, xA, yA, aHBC, bHBC, cHBC); // Height hBC (through vertex A towards side BC)
    getEquationOfHeightThroughAPoint(aAC, bAC, cAC, xB, yB, aHAC, bHAC, cHAC); // Height hAB (through vertex B towards side AC)
}

void findBisectorsOfATriangle(double xA, double yA, double xB, double yB, double xC, double yC, double& aSAB, double& bSAB, double& cSAB, double& aSBC, double& bSBC, double& cSBC, double& aSAC, double& bSAC, double& cSAC)
{
    if (suchTriangleExists(xA, yA, xB, yB, xC, yC))
    {
        double aAB, bAB, cAB, aBC, bBC, cBC, aAC, bAC, cAC;
        getEquationsOfTheSidesOfATriangle(xA, yA, xB, yB, xC, yC, aAB, bAB, cAB, aBC, bBC, cBC, aAC, bAC, cAC);

        double xMedAB = (xA + xB) / 2;
        double yMedAB = (yA + yB) / 2;
        double xMedBC = (xC + xB) / 2;
        double yMedBC = (yC + yB) / 2;
        double xMedAC = (xA + xC) / 2;
        double yMedAC = (yA + yC) / 2;
        perpendicularLine(aAB, bAB, cAB, xMedAB, yMedAB, aSAB, bSAB, cSAB);
        perpendicularLine(aBC, bBC, cBC, xMedBC, yMedBC, aSBC, bSBC, cSBC);
        perpendicularLine(aAC, bAC, cAC, xMedAC, yMedAC, aSAC, bSAC, cSAC);
    }
}

void findIntersectionPointsOfParabolaAndALine(double a, double b, double c, double aP, double bP, double cP, double& x1, double& y1, double& x2, double& y2, bool& intersect)
{
    double k, n, D;
    if (b == 0)
    {
        if (a != 0)
        {
            x1 = x2 = -c / a;
            y1 = y2 = aP * x1 * x1 + bP * x1 + cP;
            intersect = true;
        }
    }
    else
    {
        k = -a / b;    //Here we use the decartian equation of a line (y = kx + n) to find the intersection points (with the parabola) easier
        n = -c / b;
        D = (bP - k) * (bP - k) - 4 * aP * (cP - n);
        // Now we go through three different cases according to the values of the discriminant D:
        if (D > 0)
        {
            x1 = (k - bP + sqrt(D)) / (2 * aP);
            x2 = (k - bP - sqrt(D)) / (2 * aP);
            y1 = k * x1 + n;
            y2 = k * x2 + n;
            intersect = true;
        }
        else if (isEqualAbs(D, 0))
        {
            x1 = x2 = (k - bP) / (2 * a);
            y1 = y2 = k * x1 + n;
            intersect = true;
        }
        else    //(when D>0) the parabola and the line have no intersection points
        {   
            intersect = false;
        }
    }
}

void findTangentLinesOfAParabola(double a, double b, double c, double xM, double yM, double& aTangentL1, double& bTangentL1, double& cTangentL1, double& aTangentL2, double& bTangentL2, double& cTangentL2, bool& noTangentLines)
{
    double f = a * xM * xM + b * xM + c;
    double xV = -b / 2*a;
    double D = b * b - 4 * a * c;
    double x1 = (-b-sqrt(D)) / (2 * a);
    double x2 = (-b + sqrt(D)) / (2 * a);

    //Case1: The given point lies on the parabola:
     if (isEqualAbs(f, yM)) 
    {
        //in this case the equation of the tangent line "t" to the parabola at the given point is: t = f(xM) + f`(xM)*(x-xM)
        //where (xM; yM) are the coordinates of the given point
        //and f`(x) is the derivative of the function f = a*x^2 + b*x + c (which is the equation of the parabola).
        //Simplifying the above equation of the tangent line, we get the following coefficients:
        aTangentL1 = aTangentL2 = 2 * a*xM+b;
        bTangentL1 = bTangentL2 = -1;
        cTangentL1 = bTangentL2 = c - a * xM * xM;  
        noTangentLines = false;
    }   
    else if (!isEqualAbs(f,yM))
    {
        //Case 2: the given point does not lie on the parabola:
         if (a * f < 0)
         {
             noTangentLines = true;
         }
         else
         {
             double Dk = 4 * a * (a * xM * xM + b * xM + c - yM);
             aTangentL1 = b + 2 * a * xM + sqrt(Dk);
             aTangentL2 = b + 2 * a * xM - sqrt(Dk);
             bTangentL1 = bTangentL2 = -1;
             cTangentL1 = yM - aTangentL1 * xM;
             cTangentL2 = yM - aTangentL2 * xM;
             noTangentLines = false;
         }
    }
}
void kindsOfParallelograms(double kAB, double kBC, double kCD, double kAD, double AB, double BC, char* kindOfQuadrangle)
{      
        if (isEqualAbs(AB, BC))               //checks if the quarangle is a rhomb
        {
            if (isEqualAbs(kAB * kBC, -1))   //checks if the quadrangle is a square
            {
                char square[MAX_SIZE] = "square";
                copyStrings(square, kindOfQuadrangle);               
            }
            else
            {
                char rhomb[MAX_SIZE] = "rhomb";
                copyStrings(rhomb, kindOfQuadrangle);                
            }
        }
        else                                  //checks whether the quadrangle is a rectangle
        {
            if (isEqualAbs(kAB * kBC, -1))   //checks if the quadrangle is a square
            {
                char rectangle [MAX_SIZE] = "rectangle";
                copyStrings(rectangle, kindOfQuadrangle);               
            }
            else
            {
                char parallelogram[MAX_SIZE] = "parallelogram";
                copyStrings(parallelogram, kindOfQuadrangle);                
            }
        } 
}
double getProduct(double x, double y, double a, double b, double c)
{
    return(a * x + b * y + c);
}
double haveTheSameSign(double x1, double y1, double x2, double y2, double a, double b, double c)
{
    double firstVertex = getProduct(x1, y1, a, b, c);
    double secondVertex = getProduct(x2, y2, a, b, c);
    return (firstVertex * secondVertex > 0);
}
bool checkIfQuadrangleIsConvex(double xA, double yA, double xB, double yB, double xC, double yC, double xD, double yD)
{
    double aAB, bAB, cAB, aBC, bBC, cBC, aCD, bCD, cCD, aAD, bAD, cAD;
    findEquationOfALineByTwoPoints(xA, yA, xB, yB, aAB, bAB, cAB);  //gets the coefficients of the equation of the side AB (a*x + b*y + c)
    findEquationOfALineByTwoPoints(xB, yB, xC, yC, aBC, bBC, cBC);  //BC
    findEquationOfALineByTwoPoints(xD, yD, xC, yC, aCD, bCD, cCD);  //CD
    findEquationOfALineByTwoPoints(xA, yA, xD, yD, aAD, bAD, cAD);  //AD

    //Checks whether every two opposite vertexes of a line lie on its same side:
    bool pointsCandD = haveTheSameSign(xC, yC, xD, yD, aAB, bAB, cAB);
    bool pointsAandD = haveTheSameSign(xA, yA, xD, yD, aBC, bBC, cBC);
    bool pointsAandB = haveTheSameSign(xA, yA, xB, yB, aCD, bCD, cCD);
    bool pointsBandC = haveTheSameSign(xC, yC, xB, yB, aAD, bAD, cAD);

    return (pointsCandD && pointsAandD && pointsAandB && pointsBandC);
}
void determineTheKindOfQuadrangle(double aAB, double bAB, double cAB, double aBC, double bBC, double cBC, double aCD, double bCD, double cCD, double aAD, double bAD, double cAD, char* kindOfQuadrangle, bool& quadrangleExists)
{   
    bool matchingB = false;
    bool parallelB = false;
    bool matchingC = false;
    bool parallelC = false;
    bool matchingD = false;
    bool parallelD = false;
    bool matchingA = false;
    bool parallelA = false;
    double xA, yA, xB, yB, xC, yC, xD, yD;
    findIntersectionPointOfLines(aAB, bAB, cAB, aBC, bBC, cBC, xB, yB, matchingB, parallelB); //finds the coordinates of vertex B
    findIntersectionPointOfLines(aAB, bAB, cAB, aAD, bAD, cAD, xA, yA, matchingA, parallelA); //finds the coordinates of vertex A
    findIntersectionPointOfLines(aBC, bBC, cBC, aCD, bCD, cCD, xC, yC, matchingC, parallelC); //finds the coordinates of vertex C
    findIntersectionPointOfLines(aAD, bAD, cAD, aCD, bCD, cCD, xD, yD, matchingD, parallelD); //finds the coordinates of vertex D
    
    if (!matchingB && !parallelB && !matchingA && !parallelA && !matchingC && !parallelC && !matchingD && !parallelD)
    {
        quadrangleExists = true;
        double AB = findDistanceBetweenTwoPoints(xA, yA, xB, yB); // gets the length of the quadrangle's sides
        double BC = findDistanceBetweenTwoPoints(xB, yB, xC, yC);
        double CD = findDistanceBetweenTwoPoints(xC, yC, xD, yD);
        double AD = findDistanceBetweenTwoPoints(xA, yA, xD, yD);


        double kAB = (yA - yB) / (xA - xB);  //Here we get the slope coeffficient of every one of the                                 
        double kBC = (yB - yC) / (xB - xC); //four lines to check whether they are parallel, perpendicular or none of the above 
        double kCD = (yD - yC) / (xD - xC);
        double kAD = (yA - yD) / (xA - xD);
    
    
        if (isEqualAbs(kAB, kCD) && isEqualAbs(kBC, kAD))        // checks whether the quadrangle is a parallelogram
        {
            kindsOfParallelograms(kAB, kBC, kCD, kAD, AB, BC, kindOfQuadrangle); 
        }
        else if (isEqualAbs(kAB, kCD) && !isEqualAbs(kBC, kAD) || isEqualAbs(kBC, kAD) && !isEqualAbs(kAB, kCD))   //checks whether the quadrangle is a trapeze
        {
            char trapeze [MAX_SIZE] = "trapeze";
            copyStrings(trapeze, kindOfQuadrangle);           
        }
        else
        {
            if (checkIfQuadrangleIsConvex(xA, yA, xB, yB, xC, yC, xD, yD))
            {
                char convex[MAX_SIZE] = "random convex";
                copyStrings(convex, kindOfQuadrangle);               
            }
            else
            {
                char concave[MAX_SIZE] = "random concave";
                copyStrings(concave, kindOfQuadrangle);                
            }
        }
    }
    else
    {
        quadrangleExists = false;
    }   
}
void clearConsole()
{
    std::cout << "\033[;H"; // Moves cursor to the top left
    std::cout << "\033[J"; // Clears the console
}
void printDefiningALine(double& a, double& b, double& c, char* lineName)
{
    do
    {       
        std::cout << "Please define your line (p: ax + by + c) by giving it a name:" << std::endl;
        std::cin >> lineName;
        if (!validName(lineName))
        {
            std::cout << "Invalid input! Please, enter a valid name of an object!" << std::endl;
        }
    } while (!validName(lineName));
    do
    {
        std::cout << "Please, enter a number for \"a\":";
        std::cin >> a;
        std::cout << "Please, enter a number for \"b\":";
        std::cin >> b;
        std::cout << "Please, enter a number for \"c\":";
        std::cin >> c;
        if (a == 0 && b == 0)
        {            
            std::cout << "Invalid input!"<<std::endl;            
        }  
        
    } while (a == 0 && b == 0);
}
void printDefiningAPoint(double& x, double& y, char* pointName)
{
    do
    {
        std::cout << "Please define your point (x;y) by giving it a name:" << std::endl;
        std::cin >> pointName;
        if (!validName(pointName))
        {
            std::cout << "Invalid input! Please, enter a valid name of an object!" << std::endl;
        }
    } while (!validName(pointName));
  
    std::cout << "Please, enter the coordinate \"x\":";
    std::cin >> x;
    std::cout << "Please, enter the coordinate \"y\":";
    std::cin >> y;  
}
void printDefiningAParabola(double& a, double& b, double& c, char* parabolaName)
{
    do
    {
        clearConsole();
        std::cout << "Please define your parabola (p: ax^2 + bx + c) by giving it a name:" << std::endl;
        std::cin >> parabolaName;
        if (!validName(parabolaName))
        {
            std::cout << "Invalid input! Please, enter a valid name of an object!";
        }
    } while (!validName(parabolaName));

    do
    {
        std::cout << "Please, enter a number for \"a\":";
        std::cin >> a;
        std::cout << "Please, enter a number for \"b\":";
        std::cin >> b;
        std::cout << "Please, enter a number for \"c\":";
        std::cin >> c;
        if (a == 0 && b == 0 || a==0)
        {
            std::cout << "Please, enter valid coefficients a and b!";
        }       
    }while(a==0 && b==0);
}
void printOpeningMessage()
{
    clearConsole();
    std::cout << "Welcome to our Geometric world!"<<std::endl;
    std::cout << std::endl;
    std::cout << "Choose an operation from the following ones:"<<std::endl;
    std::cout << "1) Check whether a particular point lies on a given line." << std::endl;
    std::cout << "2) Find a line paralel to another through a given point." << std::endl;
    std::cout << "3) Find a line perpendicular to another in a particular point." << std::endl;
    std::cout << "4) Find the intersection point of two lines." << std::endl;
    std::cout << "5) Find the equations of the heights, medians and bisectors of a triangle." << std::endl;
    std::cout << "6) Find the equation(s) of the tangent line(s) to a parabola through a given point." << std::endl;
    std::cout << "7) Find the intersection points of a line and a parabola." << std::endl;
    std::cout << "8) Determine the kind of the quadrangle that 4 lines form." << std::endl;
}
bool validCommand(unsigned int command)
{
    return (command >= 1 && command <= 8);
}
void printLineEquation(double a, double b, double c)
{    
    if (a == 0 && b != 0)
    {
        if (c == 0)
        {
            std::cout << " the X-axis Ox. "<<std::endl;
        }
        else
        {
            std::cout << " y = " << c << std::endl;
        }
    }
    else if (a != 0 && b == 0)
    {
        if (c == 0)
        {
            std::cout << " the ordinate Oy. " << std::endl;
        }
        double p = round(- c / a);
        std::cout << "x = " << p<<std::endl;
    }
    else if(a!=0 && b!=0)
    {
        if (a == 1)
        {
            std::cout << "y = x";
        }
        else if (a == -1)
        {
            std::cout << "y = -x";
        }
        else
        {
            std::cout << "y = " << a << "*x ";
            if (c != 0)
            {
                if (c < 0)
                {
                    std::cout << c;
                }
                else
                {
                    std::cout << " + " << c;
                }
            }
        }
        std::cout << std::endl;
    }
}
void printPoint(double x, double y)
{
    std::cout << "p. (" << x << ", " << y << ")"<<std::endl;
}
void command1PointLiesOnALine()
{
    clearConsole();
    double a, b, c, x, y;
    char lineName[MAX_SIZE];
    char pointName[MAX_SIZE];

    printDefiningALine(a,b, c,lineName);    
    printDefiningAPoint(x, y,pointName);

    if (pointLiesOnTheLine(a, b, c, x, y))
    {
        std::cout << "Point " << pointName << " lies on line " << lineName << std::endl;
    }
    else
    {
        std::cout<< "Point " << pointName << " does not lie on line " << lineName << std::endl;
    }
}
void command2ParalelLine()
{
    clearConsole();
    double a, b, c, x, y, a1,b1,c1;
    char lineName[MAX_SIZE];
    char pointName[MAX_SIZE];
    printDefiningALine(a, b, c, lineName);
    printDefiningAPoint(x, y, pointName);

    parallelLine(a, b, c, x, y, a1, b1, c1);
    std::cout << "The equation of the line paralel to " << lineName << " and through point " << pointName << " is:";
    std::cout << std::endl;
    printLineEquation(a1, b1, c1);
}
void command3PerpendicularLine()
{
    clearConsole();
    double a, b, c, x, y, a1, b1, c1;
    char lineName[MAX_SIZE];
    char pointName[MAX_SIZE];
    printDefiningALine(a, b, c, lineName);
    printDefiningAPoint(x, y, pointName);

    perpendicularLine(a, b, c, x, y, a1, b1, c1);
    std::cout << "The equation of the line perpendicular to " << lineName << " in the point " << pointName << " is:"<<std::endl;
    std::cout << std::endl;
    printLineEquation(a1, b1, c1);
}
void command4IntersectionPointOfTwoLines()
{
    clearConsole();
    double a1, b1, c1, x, y, a2, b2, c2;
    bool matching = false;
    bool parallel = false;
    char firstLineName[MAX_SIZE];
    char secondLineName[MAX_SIZE];
    
    printDefiningALine(a1, b1, c1, firstLineName);
    clearConsole();
    printDefiningALine(a2, b2, c2, secondLineName);

    findIntersectionPointOfLines(a1, b1, c1, a2, b2, c2, x, y, matching, parallel);
    if (matching)
    {
        std::cout<<"The two lines are matching and have infinite amount of common points."<<std::endl;
    }
    else if (parallel)
    {
        std::cout << "The two lines are parallel and have no intersection points." << std::endl;
    }
    else
    {
        std::cout << "The intersection point of line " << firstLineName << " and line " << secondLineName << " is:"<<std::endl;
        printPoint(x,y);
    }  
}
void command5EquationsOfLinesInATriangle()
{
    clearConsole();
    double xA, yA, xB, yB, xC, yC;
    char pointAName[MAX_SIZE];
    char pointBName[MAX_SIZE];
    char pointCName[MAX_SIZE];
    printDefiningAPoint(xA, yA, pointAName);
    printDefiningAPoint(xB, yB, pointBName);
    printDefiningAPoint(xC, yC, pointCName);
    if (!suchTriangleExists(xA, yA, xB, yB, xC, yC))
    {
        do
        {
            std::cout << "Invalid input!";
            printDefiningAPoint(xA, yA, pointAName);
            printDefiningAPoint(xB, yB, pointBName);
            printDefiningAPoint(xC, yC, pointCName);
        } while (!suchTriangleExists(xA, yA, xB, yB, xC, yC));
    }
    double aMAB, bMAB, cMAB, aMBC, bMBC, cMBC, aMAC, bMAC, cMAC;
    double aHAB, bHAB, cHAB, aHBC, bHBC, cHBC, aHAC, bHAC, cHAC;
    double aSAB, bSAB, cSAB, aSBC, bSBC, cSBC, aSAC, bSAC, cSAC;

    findMediansOfATriangle(xA, yA, xB, yB, xC, yC, aMAB, bMAB, cMAB, aMBC, bMBC, cMBC, aMAC, bMAC, cMAC);
    findHeightsOfATriangle(xA, yA, xB, yB, xC, yC, aHAB, bHAB, cHAB, aHBC, bHBC, cHBC, aHAC, bHAC, cHAC);
    findBisectorsOfATriangle(xA, yA, xB, yB, xC, yC, aSAB, bSAB, cSAB, aSBC, bSBC, cSBC, aSAC, bSAC, cSAC);

    std::cout << "The equations of the medians of the triangle are:";
    std::cout << "mAB: ";
    printLineEquation(aMAB, bMAB, cMAB);
    std::cout << "mBC: ";
    printLineEquation(aMBC, bMBC, cMBC);
    std::cout << "mAC: ";
    printLineEquation(aMAC, bMAC, cMAC);

    std::cout << "The equations of the heights of the triangle are:";
    std::cout << "hAB: ";
    printLineEquation(aHAB, bHAB, cHAB);
    std::cout << "hBC: ";
    printLineEquation(aHBC, bHBC, cHBC);
    std::cout << "hAC: ";
    printLineEquation(aHAC, bHAC, cHAC);

    std::cout << "The equations of the bisectors of the triangle are:";
    std::cout << "sAB: ";
    printLineEquation(aSAB, bSAB, cSAB);
    std::cout << "sBC: ";
    printLineEquation(aSBC, bSBC, cSBC);
    std::cout << "sAC: ";
    printLineEquation(aSAC, bSAC, cSAC);
}
void command6TangentLineToAParabola()
{
    clearConsole();
    bool noLines;
    double aP, bP, cP, aTL1, bTL1, cTL1, aTL2, bTL2, cTL2;
    double xM, yM;
    char parabolaName[MAX_SIZE];
    char pointName[MAX_SIZE];
    printDefiningAPoint(xM, yM, pointName);
    printDefiningAParabola(aP,bP, cP, parabolaName);
    findTangentLinesOfAParabola(aP, bP, cP, xM, yM, aTL1, bTL1, cTL1, aTL2, bTL2, cTL2, noLines);
    if (noLines)
    {
        std::cout << "There are no tangent lines to the parabola "<<parabolaName<<" through point "<<pointName; 
   }   
    else
    {
        std::cout << "The tangent lines to the parabola " << parabolaName << " through point " << pointName << " are: "<< std::endl;
        if (aTL1 != aTL2 || bTL1 != bTL2)
        {
            printLineEquation(aTL1, bTL1, cTL1);
            printLineEquation(aTL2, bTL2, cTL2);
        }
        else
        {
            printLineEquation(aTL1, bTL1, cTL1);          
        }
    }
}
void command7IntersectionPointsOfALineAndAParabola()
{
    clearConsole();
    bool intersect = true;
    double aP, bP, cP;
    double a, b, c;
    double x1, y1, x2, y2;
    char parabolaName[MAX_SIZE];
    char lineName[MAX_SIZE];

    printDefiningAParabola(aP, bP, cP, parabolaName);
    printDefiningALine(a, b, c, lineName);

    findIntersectionPointsOfParabolaAndALine(a, b, c, aP, bP, cP, x1, y1, x2, y2, intersect);
   
    if (!intersect)
    {
        std::cout << "The parabola " << parabolaName << " and the line " <<lineName << " have no intersection points";
    }
    else 
    {
        if (x1 == x2 && y1 == y2)
        {
            std::cout <<"Point ";
            printPoint(x1, y1);
            std::cout <<" is the intersection point of the line "<<lineName<<" and the parabola "<<parabolaName;
        }
        else
        {
            std::cout << "Points ";
            printPoint(x1, y1);
            printPoint(x2, y2);
            std::cout << " are the intersection points of the line " << lineName << " and the parabola " << parabolaName;
        }        
    }  
}
void command8KindOfQuadrangle()
{
    clearConsole();
    double aAB,  bAB, cAB, aBC, bBC, cBC,aCD, bCD, cCD;
    double aAD, bAD,  cAD;
    char kindOfQuadrangle[MAX_SIZE] = "  ";
    bool quadrangleExists = true;
    char lineABName[MAX_SIZE];
    char lineBCName[MAX_SIZE];
    char lineADName[MAX_SIZE];
    char lineCDName[MAX_SIZE];
    std::cout << " side AB: "<<std::endl;
    printDefiningALine(aAB, bAB, cAB, lineABName);
    std::cout << " side BC: "<<std::endl;
    printDefiningALine(aBC, bBC, cBC, lineBCName);
    std::cout << " side CD: " << std::endl;
    printDefiningALine(aCD, bCD, cCD, lineCDName);
    std::cout << " side AD: "<<std::endl;
    printDefiningALine(aAD, bAD, cAD, lineADName);
   

    determineTheKindOfQuadrangle(aAB, bAB, cAB, aBC, bBC, cBC, aCD, bCD, cCD, aAD, bAD, cAD, kindOfQuadrangle, quadrangleExists);

    if (!quadrangleExists)
    {
        std::cout << "The four lines do not form a quadrangle."<<std::endl;
    }
    else
    {
        std::cout << "The quadrangle, formed by the four lines, is a: "<<kindOfQuadrangle<<std::endl;
    }
}
void getUsersInput()
{  
    unsigned int command;
    printOpeningMessage();
    do
    {              
        std::cin >> command;
        if (!validCommand(command))
        {
            std::cout << "Invalid input! Please, enter a valid number of a command.";
        }        
    } while (!validCommand(command));        
    
    switch (command)
    {
    case 1:command1PointLiesOnALine(); break;
    case 2: command2ParalelLine(); break;
    case 3: command3PerpendicularLine(); break;
    case 4: command4IntersectionPointOfTwoLines(); break;
    case 5: command5EquationsOfLinesInATriangle(); break;
    case 6: command6TangentLineToAParabola(); break;
    case 7: command7IntersectionPointsOfALineAndAParabola(); break;
    case 8: command8KindOfQuadrangle(); break;
    }
   // clearConsole();
}

void programExecution()
{
    char answer[SIZE];
    char negation[] = "No";
    char affirmation[] = "Yes";
    do
    {
        getUsersInput();
        std::cout << std::endl;
        std::cout << "Would you like to proceed? For our convenience, please type <Yes> or <No>."<<std::endl;
       
        std::cin >> answer;
        if (compareStrings(answer, negation))
        {
            clearConsole(); 
            std::cout << "Thank you for your participation! We would be grateful to see you again at your earliest convenience!";
            break;
        }
        else if (compareStrings(answer, affirmation))
        {
            clearConsole();
            continue;
        }
        else
        {
            std::cout << "Please, enter a valid answer (<yes> or <no>)" << std::endl;
            std::cin >> answer;             
        }
    } while (compareStrings(answer, affirmation));
}

int main()
{
  programExecution(); 
}
