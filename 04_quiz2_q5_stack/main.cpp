#include "stack.h"

int main()
{
    string s = "AABBCCDDEE";
    node *top = NULL;

    for (int i = 0; i < (int)s.length(); i++)
        push(top, s[i]);             // A A B B C C D D E E

    string rev = "";
    while (top != NULL)
        rev = rev + pop(top);        // E E D D C C B B A A

    cout << "Original : " << s << endl;
    cout << "Reversed : " << rev << endl;
    return 0;
}
