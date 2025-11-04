#include <iostream>
#include <string>
using namespace std;

class Song {
public:
    string title;
    string artist;
    float duration;
    Song* next;
    Song* prev;

    Song(string t, string a, float d) {
        title = t;
        artist = a;
        duration = d;
        next = prev = nullptr;
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:
    Playlist() {
        head = tail = current = nullptr;
    }

    void addSong(string title, string artist, float duration) {
        Song* newSong = new Song(title, artist, duration);
        if (!head) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Song added: " << title << endl;
    }

    void displayPlaylist() {
        if (!head) {
            cout << "Playlist is empty!\n";
            return;
        }
        cout << "\nCurrent Playlist:\n";
        Song* temp = head;
        int index = 1;
        while (temp) {
            cout << index++ << ". " << temp->title << " - " << temp->artist 
                 << " (" << temp->duration << " mins)\n";
            temp = temp->next;
        }
    }

    void playCurrent() {
        if (!current) {
            cout << "No song to play.\n";
            return;
        }
        cout << "\nNow Playing: " << current->title 
             << " by " << current->artist 
             << " (" << current->duration << " mins)\n";
    }

    void nextSong() {
        if (!current) {
            cout << "No songs in playlist.\n";
            return;
        }
        if (current->next) {
            current = current->next;
            playCurrent();
        } else {
            cout << "End of playlist reached.\n";
        }
    }

    void prevSong() {
        if (!current) {
            cout << "No songs in playlist.\n";
            return;
        }
        if (current->prev) {
            current = current->prev;
            playCurrent();
        } else {
            cout << "Start of playlist reached.\n";
        }
    }

    void searchSong(string title) {
        Song* temp = head;
        while (temp) {
            if (temp->title == title) {
                cout << "Found: " << temp->title << " by " 
                     << temp->artist << " (" << temp->duration << " mins)\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found: " << title << endl;
    }

    void deleteSong(string title) {
        if (!head) {
            cout << "Playlist empty.\n";
            return;
        }

        Song* temp = head;
        while (temp && temp->title != title)
            temp = temp->next;

        if (!temp) {
            cout << "Song not found.\n";
            return;
        }

        if (temp == head) head = head->next;
        if (temp == tail) tail = tail->prev;
        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;

        if (current == temp)
            current = temp->next ? temp->next : temp->prev;

        cout << "Deleted: " << temp->title << endl;
        delete temp;
    }

    ~Playlist() {
        Song* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Playlist playlist;
    int choice;
    string title, artist;
    float duration;

    do {
        cout << "\n\n========= MUSIC PLAYLIST MANAGER =========\n";
        cout << "1. Add Song\n";
        cout << "2. Display Playlist\n";
        cout << "3. Play Current Song\n";
        cout << "4. Next Song\n";
        cout << "5. Previous Song\n";
        cout << "6. Search Song\n";
        cout << "7. Delete Song\n";
        cout << "0. Exit\n";
        cout << "=============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter artist: ";
                getline(cin, artist);
                cout << "Enter duration (in mins): ";
                cin >> duration;
                playlist.addSong(title, artist, duration);
                break;

            case 2:
                playlist.displayPlaylist();
                break;

            case 3:
                playlist.playCurrent();
                break;

            case 4:
                playlist.nextSong();
                break;

            case 5:
                playlist.prevSong();
                break;

            case 6:
                cout << "Enter song title to search: ";
                getline(cin, title);
                playlist.searchSong(title);
                break;

            case 7:
                cout << "Enter song title to delete: ";
                getline(cin, title);
                playlist.deleteSong(title);
                break;

            case 0:
                cout << "Exiting Playlist Manager. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
