/* Block Comment Header
Name George Couch and Brett Smitch
Date 10/03/2021
Our multithreading assignment.
*/
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
    // Buffer between enter key so that the last key press doesn't stretch into this one
    this_thread::sleep_for(chrono::seconds(1));
    // Thread dedicated to listening for ENTER key
    while (abortAllLaunches == 0)
    {
        // Set abort to true if enter is pressed
        if (GetKeyState(VK_RETURN) & 0x8000)
        {
            abortAllLaunches = 1;
        }
    }
}

void Launch(string rocketNum)
{
    // Ensures only one thread executes this block of code at a time
        Locker.lock();
        // Executes if abortALL Launches != 1. In other words, makes check to see if enter was pressed
        if (abortAllLaunches == 0)
        {
            // Get id for current thread
            thread::id currentThread = this_thread::get_id();
            // Threads can arrive in wrong order, keeping this just for formatting from picture
            if (rocketNum == "#1")
            {
                cout << "Thread ID: " << currentThread << " has been spawned to launch rockets!\n\n" << endl;
            }
            else
            {
                cout << "Spawn thread is Launching Rocket " << rocketNum << " from spawned thread.\n" << endl;
                cout << "\tPress Enter at Space Base to stop the Space Cadet launching rockets from this spawn thread at the Rocket Pad....\n\n" << endl;
            }

            // Thread sleeps for 3 seconds
            this_thread::sleep_for(chrono::seconds(3));
            // Second check so that I can abort a launch mid initiation
            if (abortAllLaunches == 0)
            {
                cout << "*** The Space Cadet at the Rocket Pad is using the Spawn thread for Launching Local Rocket " << rocketNum << " from spawned thread.\n" << endl;
                cout << "Getting the current spawned Thread ID:" << currentThread << "\n" << endl;
            }
        }
        // Allow for other threads
        Locker.unlock();
}

int main()
{
    // Get main thread id
	thread::id mainThread = this_thread::get_id();
	cout << "\tWelcome to Rocket Launcher!\n" << endl;
	cout << "Getting the Main Thread ID:" << mainThread << endl;
	cout << "Press enter to start launching rockets locally from Space base using main thread!" << endl;
    // Press enter to continue
	cin.ignore();
	cout << "Starting to launch rockets on the Rocket Pad controlling the Launches from main thread at the Main Space Base!" << endl;
    // Thread sleeps for 3 seconds
	this_thread::sleep_for(chrono::seconds(3));
	cout << "\n\n*** Space Base using main thread is launching local Rocket #1 from Main thread at Space Base.\n" << endl;
	cout << "Space Base's Main thread is Launching Rocket #1 from Main thread at Space Base." << endl;
	cout << "Press enter to transfer control to the Space Cadet at the Space Pad to start launching rockets from spawn thread!" << endl;
    // Press enter to continue
	cin.ignore();
	cout << "Getting Main Thread ID:" << mainThread << endl;
	cout << "Press enter to stop reclaim rocket launch control from the Space Cadet at the Rocket Pad to Space Base main thread only!\n" << endl;
    // Create rocket threads
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

    // Create abort/enter key listener
    thread abort{ abortLaunch };

    // Main thread waits to join with other thread
    if (rocket1.joinable())
    {
        rocket1.join();
    }

    // Main thread waits to join with other thread
    if (rocket2.joinable())
    {
        rocket2.join();
    }

    // Main thread waits to join with other thread
    if (rocket3.joinable())
    {
        rocket3.join();
    }

    // Main thread waits to join with other thread
    if (rocket4.joinable())
    {
        rocket4.join();
    }

    // Main thread waits to join with other thread
    if (rocket5.joinable())
    {
        rocket5.join();
    }

    // Main thread waits to join with other thread
    if (rocket6.joinable())
    {
        rocket6.join();
    }

    // Main thread waits to join with other thread
    if (rocket7.joinable())
    {
        rocket7.join();
    }

    // Main thread waits to join with other thread
    if (rocket8.joinable())
    {
        rocket8.join();
    }

    // Main thread waits to join with other thread
    if (rocket9.joinable())
    {
        rocket9.join();
    }

    // Main thread waits to join with other thread
    if (rocket10.joinable())
    {
        rocket10.join();
    }

    // Occurs if Enter was pressed to abort
    if (abortAllLaunches == 1)
    {
        cout << "You Pressed enter! Space Base using Main Thread to reclaimed rocket launch control." << endl;
        cout << "About to flip abort launch switch to true!" << endl;
        cout << "Abort launch switch flipped to true!" << endl;
    }

    cout << "Checking Main Thread ID:" << mainThread << endl;
    cout << "About to Join thread, AKA wait for Thread" << endl;
    cout << "Getting Main Thread ID:" << mainThread << endl;
    // Buffer for formatting and to not let last enter press stretch into the next one
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Thread has been joined!" << endl;
    cout << "Getting Main Thread ID:" << mainThread << endl;
    cout << "Press Enter to Exit Program" << endl;
    // For some reason a normal cin.ignore wouldn't work here, this is more effective, can also activate both listeners at the same time
    while (!(GetKeyState(VK_RETURN) & 0x8000))
    {
    }

    // Join abort thread
    if (abort.joinable())
    {
        abort.join();
    }

    return 0;
}