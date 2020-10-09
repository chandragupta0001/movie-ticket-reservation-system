#include<bits/stdc++.h>
using namespace std;
class screen{
     public:
    int n,m;
    vector<vector<bool>> seats;
    set<int> aisle;
   
    screen(int n,int m,vector<int> a){
        this->n=n+1;
        this->m=m+1;
        seats.resize(n,vector<bool>(m,false));
        for(auto x :a)
        aisle.insert(x);
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
    bool suggest_contigious_seats(string screen_id,int req_seats,int row, int choice){
        screen *scr=find_screen(screen_id);
        if(!scr || scr->n<=row ||scr->m<=req_seats){
            cout<<"none"<<endl;
            return false;
        }
        vector<bool> row_status=scr->get_row_status(row);
        vector<int> seat_empty;
        
        for(auto x:row_status){
            if(x) seat_empty.push_back(0);
            else seat_empty.push_back(1);
        }
        int cap=seat_empty.size()-1;
        int temp=0,start=max(1,choice-req_seats+1),end=min(cap,choice+req_seats-1);
        // cout<<start<<end;
        for(int i=start;i<=choice;i++){
            temp=0;
            for(int j=0;j<req_seats;j++){
                // if(scr->aisle.find(i+j)!=scr->aisle.end()){
                //     temp=0;
                //     cout<<"found "<<i+j<<endl;
                //     break;
                // }
                if(i+j>end) {
                    cout<<"none1"<<endl;
                    return false;
                }
                temp+=seat_empty[i+j];
            }
            // cout<<temp;
            if(temp==req_seats &&!is_aisle(i,i+req_seats-1,scr)){
                print_seats(i,i+req_seats-1);
                return true;
            }
        }
        
        cout<<"none"<<endl;
        return false;


    }
    void print_seats(int start, int end){
        for(int i=start;i<=end;i++){
            cout<<i<<" ";
        }
        cout<<endl;
        return;
    }
    bool is_aisle(int start,int end, screen *scr){
        for(int i=start;i<end;i++){
            if(scr->aisle.find(i)!=scr->aisle.end() && scr->aisle.find(i+1)!=scr->aisle.end()){
                return true;
            }
        }
        return false;
    }
};

int main(){
    PVR pvr;
    pvr.add_screen("screen1",12,10,{4,5,8,9});
    pvr.add_screen("screen2",20,25,{3,4,12,13,17,18});
    // pvr.add_screen("screen1",12,12,{4,5,8,9});
    // screen* scr=pvr.find_screen("screen1");
    pvr.reserve_seats("screen1",{5,6,7},4);
    pvr.reserve_seats("screen2",{6,7,8,9,10},13);
    pvr.reserve_seats("screen2",{4,5,6},13);
    vector<int> empty_seat=pvr.get_unreserved("screen2",13);
     for(auto x: empty_seat)
      cout<<x<<" ";
    cout<<endl;
    //  pvr.reserve_seats("screen1",{1,3,8},2);
    //  pvr.reserve_seats("screen1",{1},2);
  
    pvr.suggest_contigious_seats("screen1",3,3,4);
      pvr.suggest_contigious_seats("screen2",4,12,4);
    pvr.suggest_contigious_seats("screen2",4,10,3);
 
    return 0;

}
/* outputs:
screen1 added
screen2 added
seat booked
seat booked
booking not possible
1 2 3 4 5 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
2 3 4
4 5 6 7
none
//@uthor Chandragupta:-)
*/