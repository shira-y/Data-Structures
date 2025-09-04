//shira yaish 327242939
//yael nave 213113889

#include <iostream>
#include <list>
#include <string>
#include "tree.h"

using namespace std;
int main()
{
	treeList tl;
	string title, father, val, son;
	char ch;
	cout << "\nDISCUSSION TREE\n";
	cout << "Choose one of the following:" << endl;
	cout << "n: New discussion tree" << endl;
	cout << "s: Add a new response" << endl;
	cout << "d: Delete a sub-discussion" << endl;
	cout << "p: Print all discussion trees" << endl;
	cout << "r: Print a sub-tree" << endl;
	cout << "w: Search a string in all discussion trees" << endl;
	cout << "e: exit:" << endl;
	do
	{
		cin >> ch;
		switch (ch)
		{
		case 'n':cout << "enter the discussion title (with no space) "; cin >> val; tl.addNewTree(val); break;
		case 's':cout << "enter the discussion title (with no space) "; cin >> title;
			cout << "enter the last message (with no space) "; cin >> father;
			cout << "enter the new respond "; cin >> son;
			if (tl.addResponse(title, father, son)) cout << "success\n"; else cout << "ERROR\n"; break;
		case 'd':cout << "enter the discussion title (with no space) "; cin >> title;
			cout << "enter string of subtree to delete (with no space) "; cin >> val;
			if (tl.delResponse(title, val)) cout << "success\n"; else cout << "ERROR\n"; break;
		case 'p':tl.printAllTrees();  break;
		case 'r':
			cout << "enter the discussion title (with no space) "; cin >> title;
			cout << "enter the last message (with no space) "; cin >> val;
			tl.printSubTree(title, val); cout << endl;  break;
		case 'w':cout << "enter a string (with no space) "; cin >> val;
			tl.searchAndPrint(val); cout << endl;  break;
		case 'e':cout << "bye "; break;
		default: cout << "ERROR\n";  break;
		}
	} while (ch != 'e');
}


/*p
Tree #1
ccc
Tree #2
bbb
Tree #3
aaa
   ddd
      eee
s
enter the discussion title (with no space) aaa
enter the last message (with no space) aaa
enter the new respond fff
success
p
Tree #1
ccc
Tree #2
bbb
Tree #3
aaa
   ddd
      eee
   fff
s
enter the discussion title (with no space) ccc
enter the last message (with no space) ccc
enter the new respond fff
success
p
Tree #1
ccc
   fff
Tree #2
bbb
Tree #3
aaa
   ddd
      eee
   fff
d
enter the discussion title (with no space) aaa
enter string of subtree to delete (with no space) ddd
success
p
Tree #1
ccc
   fff
Tree #2
bbb
Tree #3
aaa
   fff
s
enter the discussion title (with no space) aaa
enter the last message (with no space) aaa
enter the new respond ggg
success
s
enter the discussion title (with no space) aaa
enter the last message (with no space) aaa
enter the new respond hhh
success
p
Tree #1
ccc
   fff
Tree #2
bbb
Tree #3
aaa
   fff
   ggg
   hhh
s
enter the discussion title (with no space) aaa
enter the last message (with no space) ggg
enter the new respond iii
success
s
enter the discussion title (with no space) aaa
enter the last message (with no space) iii
enter the new respond jjj
success
s
enter the discussion title (with no space) aaa
enter the last message (with no space) bbb
enter the new respond ddd
ERROR
s
enter the discussion title (with no space) ttt
enter the last message (with no space) fff
enter the new respond ggg
ERROR
s
enter the discussion title (with no space) aaa
enter the last message (with no space) hhh
enter the new respond kkk
success
p
Tree #1
ccc
   fff
Tree #2
bbb
Tree #3
aaa
   fff
   ggg
      iii
         jjj
   hhh
      kkk
r
enter the discussion title (with no space) aaa
enter the last message (with no space) ggg

ggg
   iii
      jjj
ggg=>aaa
s
enter the discussion title (with no space) bbb
enter the last message (with no space) bbb
enter the new respond fff
success
s
enter the discussion title (with no space) bbb
enter the last message (with no space) fff
enter the new respond fff
success
pe
Tree #1
ccc
   fff
Tree #2
bbb
   fff
      fff
Tree #3
aaa
   fff
   ggg
      iii
         jjj
   hhh
      kkk
w
enter a string (with no space) www
ERROR
w
enter a string (with no space) fff
fff
fff=>ccc
fff
   fff
fff=>bbb
fff
fff=>aaa
w
enter a string (with no space) jjj
jjj
jjj=>iii=>ggg=>aaa
e
bye
*/