#include<bits/stdc++.h>
using namespace std;
class screen{
    int n,m;
    vector<vector<bool>> seats;
    vector<int> aisle;
    public:
    screen(int n,int m,vector<int> aisle){
        this->n=n+1;
        this->m=m+1;
        seats.resize(n,vector<bool>(m,false));
        this->aisle=aisle;
    }
    void screen_stat();
    vector<int> get_empty_row(int row);
    vector<bool> get_row_status(int row);
    void book_seat(vector<int> seats_to_book,int row);
    
};
void screen::screen_stat(){
        cout<<n<<" "<<m<<" "<<endl;
    }
vector<int> screen::get_empty_row(int row){
        vector<int> ans;
        for(int i=1;i<m;i++){
            if(!seats[row][i]) ans.push_back(i);
        }
        return ans;
    }
vector<bool> screen:: get_row_status(int row){
        return seats[row];
    }
void screen::book_seat(vector<int> seats_to_book,int row){
          for(auto x:seats_to_book){
              seats[row][x]=true;
          }
    }

class PVR{
    public:
    list<screen*> screens;
    map<string,screen*> present_screens;
    
    bool add_screen(string screen_id,int n,int m, vector<int> aisle){
        if(present_screens.find(screen_id)!=present_screens.end()) {
            cout<<"screen "<<screen_id<<" already exist"<<endl;
            return false;}
        screen *s=new screen(n,m,aisle);
        present_screens[screen_id]=s;
        screens.push_back(s);
        // cout<<s<<endl;
        // // screens.front()->screen_stat();
        
        cout<<screen_id<<" added"<<endl;
        return true;
    }
    screen* find_screen(string screen_id){
        if(present_screens.find(screen_id)!=present_screens.end()) return present_screens[screen_id];
        return nullptr;
    }
    vector<int> get_unreserved(string screen_id, int row){
        screen* scr=find_screen(screen_id);
        if(!scr) return {};
        return scr->get_empty_row(row);

    }
    bool reserve_seats(string screen_id,vector<int> seats_to_book,int row){
           screen *scr=find_screen(screen_id);
           if(!scr) return false;
           vector<bool> row_status=scr->get_row_status(row);
           if(is_avaliable(row_status,seats_to_book)){
                     scr->book_seat(seats_to_book,row);
                     cout<<"seat booked"<<endl;
                     return true;
           }
           else {
               cout<<"booking not possible"<<endl;
               return false;
           }
    }
    bool is_avaliable(vector<bool>& row_status,vector<int> &seats_to_book){
        int row_cap=row_status.size();
        for(auto x:seats_to_book)
        if(x>=row_cap ||row_status[x]) return false;
        return true;
    }
};

int main(){
    PVR pvr;
    pvr.add_screen("screen1",12,10,{4,5,8,9});
    pvr.add_screen("screen2",20,25,{3,4,12,13,17,18});
    pvr.add_screen("screen1",12,12,{4,5,8,9});
    // screen* scr=pvr.find_screen("screen1");
    pvr.reserve_seats("screen1",{5,6,7},4);
    pvr.reserve_seats("screen2",{6,7,8,9,10},13);
    pvr.reserve_seats("screen2",{4,5,6},13);
    vector<int> empty_seat=pvr.get_unreserved("screen2",13);
     for(auto x: empty_seat)
      cout<<x<<" ";
      cout<<endl;
     pvr.reserve_seats("screen1",{1,3,8},2);
     pvr.reserve_seats("screen1",{1},2);
   
 
    return 0;

}
//@uthor Chandragupta:-)