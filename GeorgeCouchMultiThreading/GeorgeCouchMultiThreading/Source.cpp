#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <Windows.h>
using namespace std;

mutex Locker;

int abortAllLaunches = 0;

void abortLaunch()
{
    // George: Buffer between enter key so that the last key press doesn't stretch into this one
    this_thread::sleep_for(chrono::seconds(1));
    while (abortAllLaunches == 0)
    {
        if (GetKeyState(VK_RETURN) & 0x8000)
        {
            abortAllLaunches = 1;
        }
    }
}

void Launch(string rocketNum)
{
        Locker.lock();
        if (abortAllLaunches == 0)
        {
            thread::id currentThread = this_thread::get_id();
            // George: Threads can arrive in wrong order, keeping this just for formatting from picture
            if (rocketNum == "#1")
            {
                cout << "Thread ID: " << currentThread << " has been spawned to launch rockets!\n\n" << endl;
            }
            else
            {
                cout << "Spawn thread is Launching Rocket " << rocketNum << " from spawned thread.\n" << endl;
                cout << "\tPress Enter at Space Base to stop the Space Cadet launching rockets from this spawn thread at the Rocket Pad....\n\n" << endl;
            }

            this_thread::sleep_for(chrono::seconds(3));
            // George: Second check so that I can abort a launch mid initiation
            if (abortAllLaunches == 0)
            {
                cout << "*** The Space Cadet at the Rocket Pad is using the Spawn thread for Launching Local Rocket " << rocketNum << " from spawned thread.\n" << endl;
                cout << "Getting the current spawned Thread ID:" << currentThread << "\n" << endl;
            }
        }
        Locker.unlock();
}

int main()
{
	thread::id mainThread = this_thread::get_id();
	cout << "\tWelcome to Rocket Launcher!\n" << endl;
	cout << "Getting the Main Thread ID:" << mainThread << endl;
	cout << "Press enter to start launching rockets locally from Space base using main thread!" << endl;
	cin.ignore(); // George: This can cause a bug where I have to press enter twice here, so far fixed by saving program and running again (CTRL + S)
	cout << "Starting to launch rockets on the Rocket Pad controlling the Launches from main thread at the Main Space Base!" << endl;
	this_thread::sleep_for(chrono::seconds(3)); //George: can possibly change this to Dragon Fight format so looks better with ...
	cout << "\n\n*** Space Base using main thread is launching local Rocket #1 from Main thread at Space Base.\n" << endl;
	cout << "Space Base's Main thread is Launching Rocket #1 from Main thread at Space Base." << endl;
	cout << "Press enter to transfer control to the Space Cadet at the Space Pad to start launching rockets from spawn thread!" << endl;
	cin.ignore();
	cout << "Getting Main Thread ID:" << mainThread << endl;
	cout << "Press enter to stop reclaim rocket launch control from the Space Cadet at the Rocket Pad to Space Base main thread only!\n" << endl;
	thread rocket1{ Launch,"#1" };
	thread rocket2{ Launch,"#2" };
	thread rocket3{ Launch,"#3" };
	thread rocket4{ Launch,"#4" };
	thread rocket5{ Launch,"#5" };
	thread rocket6{ Launch,"#6" };
	thread rocket7{ Launch,"#7" };
	thread rocket8{ Launch,"#8" };
	thread rocket9{ Launch,"#9" };
	thread rocket10{ Launch,"#10" };
    thread abort{ abortLaunch };

    if (rocket1.joinable())
    {
        rocket1.join();
    }

    if (rocket2.joinable())
    {
        rocket2.join();
    }

    if (rocket3.joinable())
    {
        rocket3.join();
    }

    if (rocket4.joinable())
    {
        rocket4.join();
    }

    if (rocket5.joinable())
    {
        rocket5.join();
    }

    if (rocket6.joinable())
    {
        rocket6.join();
    }

    if (rocket7.joinable())
    {
        rocket7.join();
    }

    if (rocket8.joinable())
    {
        rocket8.join();
    }

    if (rocket9.joinable())
    {
        rocket9.join();
    }

    if (rocket10.joinable())
    {
        rocket10.join();
    }

    if (abortAllLaunches == 1)
    {
        cout << "You Pressed enter! Space Base using Main Thread to reclaimed rocket launch control." << endl;
        cout << "About to flip abort launch switch to true!" << endl;
        cout << "Abort launch switch flipped to true!" << endl;
    }

    cout << "Checking Main Thread ID:" << mainThread << endl;
    cout << "About to Join thread, AKA wait for Thread" << endl;
    cout << "Getting Main Thread ID:" << mainThread << endl;
    // George: Buffer for potential formatting and to not let last enter press stretch into the next one
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Thread has been joined!" << endl;
    cout << "Getting Main Thread ID:" << mainThread << endl;
    cout << "Press Enter to Exit Program" << endl;
    // George: For some reason a normal cin.ignore wouldn't work here, this is more effective, can also activate both listeners at the same time
    while (!(GetKeyState(VK_RETURN) & 0x8000))
    {
    }

    // George: Placed abort.join down here so that it's loop will end for sure given that you must press enter to get here, could also just call exit() and not join
    if (abort.joinable())
    {
        abort.join();
    }

    return 0;
}