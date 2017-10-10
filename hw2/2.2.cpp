#include <cstdio>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;
#define NUM 73209277

typedef struct Ownitemnum
{
    int UserId;
    int amount;
    Ownitemnum () {};
    Ownitemnum (int u ,int a) {
        UserId = u;
        amount = a;
    }
    bool operator == (const Ownitemnum temp) const
    {
        return (UserId == temp.UserId) &&
               (amount == temp.amount);
    }
}ownitemnum;

typedef struct data
{
	int UserId;
	int ItemId;
	short int Result;
	int timestamp;
    data () {};
    data (int u ,int i ,int a,int t) {
        UserId = u;
        ItemId = i;
        Result = a;
        timestamp = t;
    }
    bool operator == (const data temp) const
    {
        return (UserId == temp.UserId) &&
               (ItemId == temp.ItemId) &&
               (timestamp == temp.timestamp);
    }
}Data;

Data list;
vector<Data> vecbytime;
vector<Data> vecbyitem;
vector<Data> vecbyuser;
vector<ownitemnum> plate;
ownitemnum x;

bool cmp(int a, int b)
{
    return a < b;
}

bool cmp_by_userid(Data a, Data b)
{
    //return a.UserId < b.UserId;
    if(a.UserId != b.UserId){
        return a.UserId < b.UserId;
    }
    if(a.ItemId != b.ItemId){
        return a.ItemId < b.ItemId;
    }
    if(a.timestamp != b.timestamp){
        return a.timestamp < b.timestamp;
    }
    return a.timestamp < b.timestamp;
}

bool cmp_by_itemid(Data a, Data b)
{
    return a.ItemId < b.ItemId;
    /*if(a.ItemId > b.ItemId){
        return a.ItemId < b.ItemId;
    }
    return a.timestamp < b.timestamp;*/
}

int findtime(int timee, int n){
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (vecbytime[mid].timestamp == timee)
        {
            return mid;
        }
        else if (vecbytime[mid].timestamp > timee)
        {
            high = mid - 1;
        }
        else if (vecbytime[mid].timestamp < timee)
        {
            low = mid + 1;
        }
    }
    return -1;
}

int finduser(int user, int n){
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (vecbyuser[mid].UserId == user)
        {
            return mid;
        }
        else if (vecbyuser[mid].UserId > user)
        {
            high = mid - 1;
        }
        else if (vecbyuser[mid].UserId < user)
        {
            low = mid + 1;
        }
    }
    return -1;
}

int finditem(int item, int n){
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (vecbyitem[mid].ItemId == item)
        {
            return mid;
        }
        else if (vecbyitem[mid].ItemId > item)
        {
            high = mid - 1;
        }
        else if (vecbyitem[mid].ItemId < item)
        {
            low = mid + 1;
        }
    }
    return -1;
}

int userstart(int user, int now){
    for(int i = now; i >= 0; i--){
        if(vecbyuser[i].UserId < user){
            return i + 1;
        }
        if(i == 0){
            return i;
    	}
    }
}

int userend(int user, int now){
    int size = vecbytime.size();
    for(int i = now; i < size; i++){
        if(vecbyuser[i].UserId > user){
            return i - 1;
        }
        if(i == vecbytime.size()){
            return i;
    	}
    }
}

int startime(int timee, int now){
    for(int i = now; i >= 0; i--){
    	if(vecbytime[i].timestamp != timee){
    		return i + 1;
    	}
    	if(i == 0){
            return i;
    	}
    }
}

int endtime(int timee, int now){
    int size = vecbytime.size();
    for(int i = now; i < size; i++){
        if(vecbytime[i].timestamp != timee){
            return i - 1;
        }
        if(i == vecbytime.size()){
            return i;
    	}
    }
}

int itemstart(int item, int now){
    for(int i = now; i >= 0; i--){
        if(vecbyitem[i].ItemId < item){
            return i + 1;
        }
        if(i == 0){
            return i;
    	}
    }
}

int itemend(int item, int now){
    int size = vecbytime.size();
    for(int i = now; i < size; i++){
        if(vecbyitem[i].ItemId > item){
            return i - 1;
        }
        if(i == vecbytime.size()){
            return i;
    	}
    }
}

int range(int now){
    int id = vecbyuser[now].UserId;
    int size = vecbyuser.size();
    for(int i = now; i < size; i++){
        if(vecbyuser[i].UserId != id){
            return (i - now);
        }
    }
    return (size - now);
}

int owned(int itemtofind, int loc){
    int found = 0;
    int id = vecbyuser[loc].UserId;
    int size = vecbyuser.size();
    for(int i = userstart(id, loc); i < size; i++){
        if(vecbyuser[i].UserId != id){
            return 0;
        }
        if(vecbyuser[i].ItemId == itemtofind && vecbyuser[i].Result == 1){
            return 1;
        }
    }
    return 0;
}

void accept(int user, int item, int timee){
    int loc = findtime(timee, vecbytime.size());
    int flag = 0;
    if(loc < 0){
        loc = 0;
        return;
    }
    int start = startime(timee, loc);
    int size = vecbytime.size();
    for(int i = start; i < size; i++){
    	if(vecbytime[i].UserId == user && vecbytime[i].ItemId == item && vecbytime[i].timestamp == timee){
    		printf("%d\n", vecbytime[i].Result);
            flag = 1;
            break;
    	}
        if(vecbytime[i].timestamp != timee){
            break;
        }
    }
    if(flag == 0){
        printf("0\n");
    }
}

void items(int user1,int user2){
    int flag = 0;
    int start1, end1, start2, end2;
    vector<int> itemtoprint;
    int user1loc = finduser(user1, vecbyuser.size());
    start1 = userstart(user1, user1loc);
    end1= userend(user1, user1loc);
    int user2loc = finduser(user2, vecbyuser.size());
    start2 = userstart(user2, user2loc);
    end2= userend(user2, user2loc);
    for(int i = start1; i <= end1; i++){
        for(int j = start2; j <= end2; j++){
            if(vecbyuser[i].ItemId == vecbyuser[j].ItemId){
                itemtoprint.push_back(vecbyuser[i].ItemId);
                flag = 1;
            }
        }
    }
    sort(itemtoprint.begin(), itemtoprint.end(), cmp);
    int newsize2 = unique(itemtoprint.begin(), itemtoprint.end()) - itemtoprint.begin();
    itemtoprint.resize(newsize2);
    for(int i = 0; i < itemtoprint.size(); i++){
        printf("%d\n", itemtoprint[i]);
    }
    if(flag == 0){
        printf("EMPTY\n");
    }
}

void users(int item1, int item2, int time1, int time2){
    int flag = 0;
    vector<int> memberlist1;
    vector<int> memberlist2;
    int item1loc = finditem(item1, vecbyitem.size());
    int start = itemstart(item1, item1loc);
    int end = itemend(item1, item1loc);
    int item2loc = finditem(item2, vecbyitem.size());
    for(int i = start; i <= end; i++){
        if(vecbyitem[i].timestamp >= time1 && vecbyitem[i].timestamp <= time2){
            memberlist1.push_back(vecbyitem[i].UserId);
        }
    }
    start = itemstart(item2, item2loc);
    end = itemend(item2, item2loc);
    for(int i = start; i <= end; i++){
        if(vecbyitem[i].timestamp >= time1 && vecbyitem[i].timestamp <= time2){
            memberlist2.push_back(vecbyitem[i].UserId);
        }
    }
    sort(memberlist1.begin(),memberlist1.end(),cmp);
    int newsize3 = unique(memberlist1.begin(),memberlist1.end()) - memberlist1.begin();
    memberlist1.resize(newsize3);
    sort(memberlist2.begin(),memberlist2.end(),cmp);
    int newsize5 = unique(memberlist2.begin(),memberlist2.end()) - memberlist2.begin();
    memberlist2.resize(newsize5);
    for(int i = 0; i < memberlist1.size(); i++){
        for(int j = 0; j < memberlist2.size(); j++){
            if(memberlist1[i] == memberlist2[j]){
                printf("%d\n", memberlist1[i]);
                flag = 1;
            }
        }
    }
    if(flag == 0){
        printf("EMPTY\n");
    }
}
void ratio(int i0, int threshold){
    int total = 0, acception = 0;
    int flag1 = 0, size = plate.size();
    for(int k = 0; k < size; k++){
        if(plate[k].amount > threshold){
            total ++;
            int place = finduser(plate[k].UserId, vecbyuser.size());
            flag1 = 0;
            flag1 = owned(i0, place);
            if(flag1 == 1){
                acception ++;
            }
        }
    }
    printf("%d/%d\n", acception, total);
}
void findtime_item(int i0, vector<int> &Us){
    vector<int> timelist;
    int itemloc = finditem (i0, vecbyitem.size());
    int start = itemstart(i0, itemloc);
    int end = itemend(i0, itemloc);
    for(int j = start; j <= end; j++){
        for(int k = 0; k < Us.size(); k++){
            if(vecbyitem[j].UserId == Us[k]){
                timelist.push_back(vecbyitem[j].timestamp);
            }
        }
    }
    sort(timelist.begin(), timelist.end(), cmp);
    int newsize4 = unique(timelist.begin(), timelist.end()) - timelist.begin();
    timelist.resize(newsize4);
    int size = timelist.size();
    for(int q = 0; q < size; q++){
        printf("%d\n", timelist[q]);
    }
    if(timelist.size() == 0){
        printf("EMPTY\n");
    }
}
int main(void){
    int a,b,c,d;
    FILE *fp = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt","rb");
    while(fscanf(fp, "%d%d%d%d", &list.UserId, &list.ItemId, &list.Result, &list.timestamp) != EOF){
        vecbytime.push_back(list);
    }
    fclose(fp);
    vecbyuser = vecbytime;
    sort(vecbyuser.begin(), vecbyuser.end(), cmp_by_userid);
    int newsize = unique(vecbyuser.begin(), vecbyuser.end()) - vecbyuser.begin();
    vecbyuser.resize(newsize);
    int size = vecbyuser.size();
    for(int l = 0; l < size; l++){
        x.UserId = vecbyuser[l].UserId;
        x.amount = range(l);
        plate.push_back(x);
        l += x.amount - 1;
    }
    plate.push_back(x);
    int newsize6 = unique(plate.begin(), plate.end()) - plate.begin();
    plate.resize(newsize6);
    vecbyitem = vecbytime;
    sort(vecbyitem.begin(), vecbyitem.end(), cmp_by_itemid);
    int n, u, i0, t, u1, u2, i1, i2, t1, t2, threshold, tempuser;
    char command[20]={'\0'};
    scanf("%d",&n);
    while(n--){
        scanf("%s", &command);

        if(strcmp(command, "accept") == 0){
           scanf("%d%d%d", &u, &i0, &t);
           accept(u,i0,t);
        }
        if(strcmp(command, "items") == 0){
            scanf("%d%d", &u1, &u2);
            items(u1,u2);
        }
        if(strcmp(command, "users") == 0){
            scanf("%d%d%d%d",&i1 ,&i2 ,&t1, &t2);
            users(i1,i2,t1,t2);
        }
        if(strcmp(command, "ratio") == 0){
            scanf("%d%d", &i0, &threshold);
            ratio(i0,threshold);
        }
        if(strcmp(command, "findtime_item") == 0){
            scanf("%d",&i0);
            string s;
            getline(cin, s);
            vector<int> Uss;
            int tempinput;
            istringstream input(s);
            while(input >> tempinput){
                Uss.push_back(tempinput);
            }
            sort(Uss.begin(), Uss.end(),cmp);
            int newsize1 = unique(Uss.begin(), Uss.end()) - Uss.begin();
            Uss.resize(newsize1);
            findtime_item(i0,Uss);
        }
    }
    return 0;
}