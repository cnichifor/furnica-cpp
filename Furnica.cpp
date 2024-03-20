// #include<iostream>
// #include<fstream>
#include<bits/stdc++.h>
using namespace std;

int n, k, r = 2, mx = 1;
ifstream read("Furnica.in");
ofstream write("Furnica.out");
pair<int, int> table[101][101], F(0, 0);
int moves[201];

int one(int a){
    if(a == 1)
        return 0;
    else
        return 1;
}

void displaymenu()
{ cout<<"===================================================== \n";
cout<<" \t\tMENU \t \n ";
cout<<"===================================================== \n";
cout<<" 1.Extinde drumul furnicii\n";
cout<<" 2.Exclude din drumul furnicii\n";
cout<<" 3.Initializare matrice patratica\n";
cout<<" 4.Frecventa cifrelor\n";
cout<<" 5.Afiseaza elementele liniei L(sortate)\n";
cout<<" 6.Creare UnZero.txt\n";
cout<<" 7.Gaseste submatrice ce nu contine 1(sortate)\n";
cout<<" 8.Salveaza raspuns\n";
cout<<" 9.Salvare modificari si inchidere\n";
}

void Table(){
    table[0][0].second = 1;
    read >> n >> k;
    for(int i = 0; i < k; i++)
        read >> moves[i];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            table[i][j] = {(i + j + 2) % 6, 0};
        }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << table[i][j].first << " ";
        }
        cout << "\n";
     }
}

void AfisTable(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << table[i][j].first << " ";
        }
        cout << "\n";
     }
     cout << "\n";
}

void Move(int d){
    int x = F.second, y = F.first;
        switch (d){
        case 1:
            y -= 1;
            break;
        case 2:
            y -= 1;
            x += 1;
            break;
        case 3:
            x += 1;
            break;
        case 4:
            y += 1;
            x += 1;
            break;
        case 5:
            y += 1;
            break;
        case 6:
            y += 1;
            x -= 1;
            break;
        case 7:
            x -= 1;
            break;
        case 8:
            y -= 1;
            x -= 1;
            break;
        
        default:
            break;
        }
        if(x >= 0 || y >= 0)
            F = {y, x};
        r += table[y][x].first;
        table[y][x].first = 0;
        table[y][x].second++;
        if(mx < table[y][x].second)
            mx = table[y][x].second;
}

int Max(){
    int c = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(table[i][j].second == mx)
                c++;
    return c;
}

void AddMove(){
    cout << "Introduceti numarul directiei: ";
    cin >> moves[k];
    k += 1;
}

void DeleteMove(){
    moves[k - 1] = 0;
    k -= 1;
    cout << "Exclus cu succes!\n";
}

void Frequency(){
    int mx;
    for(int t = 0; t <= 5; t++){
        mx = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++){
                if(table[i][j].first == t)
                    mx++;
            }
        cout << t << " - " << mx << " ori\n";
    }
}

void SortL(){
    int l, arr[n];
    cout << "Introduceti L: ";
    cin >> l;
    for(int j = 0; j < n; j++)
        arr[j] = table[l - 1][j].first;

    int minidx;
    for (int i = 0; i < n - 1; i++)
    {
       
        minidx = i;
        for (int j = i + 1; j < n; j++)
        if (arr[j] < arr[minidx])
            minidx = j;
 
        swap(arr[minidx], arr[i]);
    }

    for(int j = 0; j < n; j++)
        cout << arr[j] << " ";
    cout << "\n";
}

void UnZero(){
    int z;
    ofstream zero("UnZero.txt");
    for(int i = 0; i < n; i++){
        z = 0;
        for(int j = 0; j < n; j++){
            if(table[i][j].first == 0)
                z++;
        }
        if(z == 1){
            for(int j = 0; j < n; j++)
                zero << table[i][j].first << " ";
            zero << "\n";
        }
    }
    cout << "Creat cu succes!\n";
}

void MaxSubSquare(){
    int arr[101][101];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(one(table[i][j].first)){
                if(i == 0 || j == 0)
                    arr[i][j] = 1;
                else
                    arr[i][j] = 1 + min(min(arr[i - 1][j], arr[i - 1][j - 1]), arr[i][j - 1]); 
            }
            else arr[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }

    int mx = 0, mi, mj;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mx < arr[i][j])
                mx = arr[i][j];
                mi = i; mj = j;
        }
    }
    cout << "\n";cout << "\n";
   for(int i = mi - mx; i < mi; i++){
       for(int j = mj - mx; j < mj; j++){
           cout << table[i][j].first << " ";
       }
       cout << "\n";
   }

}

void Solve(){
    table[0][0].first = 0;
    for(int i = 0; i < k; i++){
        Move(moves[i]);
        cout << "Move " << i + 1 << "\n_________________________\n";
        AfisTable();
        cout << "\n";
    }
    write << r << " " << Max();
}

void Finish(){
    read.close();
    ofstream read("Furnica.in");
    read << n << " " << k << "\n";
    for(int i = 0; i < k; i++)
        read << moves[i] << " ";
}

int main(){

    displaymenu(); 
    int yourchoice;
    string confirm;
    do{ 
    cout<<"Intruduce-ti alegerea(1-9): ";
    cin>>yourchoice;
    switch (yourchoice){
        case 1: AddMove(); break;
        case 2: DeleteMove();break;
        case 3: Table(); break;
        case 4: Frequency();break;
        case 5: SortL();break;
        case 6: UnZero();break;
        case 7: MaxSubSquare();break;
        case 8: Solve();break;
        case 9: Finish();break;
        default: cout<<"invalid\n";break;
    }
    cout << "Alegeti orice pentru a continua: ";
    cin >> confirm;
    } while (yourchoice != 9);
return 0;

    

    return 0;
}