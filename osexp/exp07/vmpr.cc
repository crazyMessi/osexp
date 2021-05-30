/*
* Filename : vmrp.cc
* copyright : (C) 2006 by zhonghonglie
* Function : 模拟虚拟内存页置换算法的程序
*/
#include "vmpr.h"
#include <vector>
using namespace std;
#include <assert.h>
void getRadomR(int *array, int size,int range)
{
   for (int i = 0; i < size-3; i+=4){
        array[i] = 5 + random()%5;
        array[i+1] = i%10;
        array[i+2] = i%10;
        array[i+3] = i%5;
    } 
}

Replace::Replace()
{
    int i;
    //设定总得访问页数,并分配相应的引用页号和淘汰页号记录数组空间
    cout << "Please input page numbers and range:";
    int range;
    cin >> PageNumber >>range;                                 //存放要访问到的页号
    ReferencePage = new int[sizeof(int) * PageNumber]; //访问页数
    EliminatePage = new int[sizeof(int) * PageNumber]; //存放淘汰页号
    getRadomR(ReferencePage, PageNumber,range);
    cout << "Please input page frames :";
    cin >> FrameNumber;                              //实存帧数
    PageFrames = new int[sizeof(int) * FrameNumber]; //存放当前正在实存中的页号
}
Replace::~Replace()
{
}
void Replace::InitSpace(char *MethodName)
{
    int i;
    cout << endl
         << MethodName << endl;
    FaultNumber = 0;
    //引用还未开始,-1表示无引用页
    for (i = 0; i < PageNumber; i++)
        EliminatePage[i] = -1;
    for (i = 0; i < FrameNumber && i < PageNumber; i++)
        PageFrames[i] = -1;
}
//分析统计选择的算法对于当前输入的页面走向的性能
void Replace::Report(void)
{
#ifdef CHECK
    //报告淘汰页顺序
    cout << endl
         << "Eliminate page:";
    for (int i = 0; EliminatePage[i] != -1; i++)
        cout << EliminatePage[i] << " ";
//报告缺页数和缺页率
#endif
    cout << endl
         << "Number of page faults = " << FaultNumber << endl;
    cout << setw(6) << setprecision(3);
    cout << "Rate of page faults = " << 100 * (float)FaultNumber / (float)PageNumber << "%" << endl;
}
//最近最旧未用置换算法
void Replace::Lru(void)
{
    int i, j, k, l, next;
    InitSpace("LRU");
    //循环装入引用页
    for (k = 0, l = 0; k < PageNumber; k++)
    {
        next = ReferencePage[k];
        //检测引用页当前是否已在实存
        for (i = 0; i < FrameNumber; i++)
        {
            if (next == PageFrames[i])
            {
                //引用页已在实存将其调整到页记录栈顶
                next = PageFrames[i];
                for (j = i; j > 0; j--)
                    PageFrames[j] = PageFrames[j - 1];
                PageFrames[0] = next;
                break;
            }
        }
        if (PageFrames[0] == next)
        {
#ifdef CHECK
            //如果引用页已放栈顶，则为不缺页，报告当前内存页号
            for (j = 0; j < FrameNumber; j++)
                if (PageFrames[j] >= 0)
                    cout << PageFrames[j] << " ";
            cout << endl;
#endif
            continue; //继续装入下一页
        }
        else
            // 如果引用页还未放栈顶，则为缺页，缺页数加1
            FaultNumber++;
        //栈底页号记入淘汰页数组中
        EliminatePage[l] = PageFrames[FrameNumber - 1];
        //向下压栈
        for (j = FrameNumber - 1; j > 0; j--)
            PageFrames[j] = PageFrames[j - 1];
        PageFrames[0] = next; //引用页放栈顶
                              //报告当前实存中页号

#ifdef CHECK
        for (j = 0; j < FrameNumber; j++)
            if (PageFrames[j] >= 0)
                cout << PageFrames[j] << " ";
        //报告当前淘汰的页号
        if (EliminatePage[l] >= 0)
            cout << "->" << EliminatePage[l++] << endl;
        else
            cout << endl;
#endif
    }
    //分析统计选择的算法对于当前引用的页面走向的性能
    Report();
}
//先进先出置换算法
void Replace::Fifo(void)
{
    int i, j, k, l, next;
    InitSpace("FIFO");
    //循环装入引用页
    for (k = 0, j = l = 0; k < PageNumber; k++)
    {
        next = ReferencePage[k];
        //如果引用页已在实存中，报告实存页号
        for (i = 0; i < FrameNumber; i++)
            if (next == PageFrames[i])
                break;
        if (i < FrameNumber)
        {
#ifdef CHECK
            for (i = 0; i < FrameNumber; i++)
                cout << PageFrames[i] << " ";
            cout << endl;
#endif
            continue; // 继续引用下一页

        }
        //引用页不在实存中，缺页数加1
        FaultNumber++;
        EliminatePage[l] = PageFrames[j]; //最先入页号记入淘汰页数组
        PageFrames[j] = next;             //引用页号放最先入页号处
        j = (j + 1) % FrameNumber;        //最先入页号循环下移
#ifdef CHECK
        //报告当前实存页号和淘汰页号
        for (i = 0; i < FrameNumber; i++)
            if (PageFrames[i] >= 0)
                cout << PageFrames[i] << " ";
        if (EliminatePage[l] >= 0)
            cout << "->" << EliminatePage[l++] << endl;
        else
            cout << endl;
#endif
    }
    //分析统计选择的算法对于当前引用的页面走向的性能
    Report();
}
//未实现的其他页置换算法入口
void Replace::Eclock(void)
{
    int next;
    int min;
    bool flag;
    int elim_index;
    InitSpace("ECLOCK");

    //using a vector instead of a array
    vector<eclock> my_PageFrames;

    for (size_t i = 0; i < PageNumber; i++)
    {
        flag = false;
        next = ReferencePage[i];

        //find out if frame exists
        for (size_t j = 0; j < my_PageFrames.size(); j++)
        {
            //giving the aim a second chance
            if (my_PageFrames[j].first == next)
            {
                if (my_PageFrames[j].second < 2)
                {
                    my_PageFrames[j].second += 2;
                }
                flag = true;
                break;
            }
        }
        //if not exists,Fage error
        if (!flag)
        {
            //FaultNumber>=FrameNumber means elimination
            //serch for the min and elimiate it
            if (FaultNumber >= FrameNumber)
            {
                elim_index = 0;
                min = 3;
                assert(my_PageFrames.size() == FrameNumber);
                for (size_t j = 0; j < FrameNumber && min; j++)
                {
                    if (my_PageFrames[j].second < min)
                    {
                        min = my_PageFrames[j].second;
                        elim_index = j;
                    }
                }

                //if the elim one is not the first frame in queue,modify the frame before it
                if (elim_index > 0)
                {
                    for (int j = 0; j < elim_index; j++)
                    {
                        my_PageFrames[elim_index].second--;
                    }
                }
                EliminatePage[FaultNumber - FrameNumber] = my_PageFrames[elim_index].first;
                my_PageFrames.erase(my_PageFrames.begin() + elim_index);
            }
            eclock e = make_pair(next, 0);
            my_PageFrames.push_back(e);
            FaultNumber++;
        }
#ifdef CHECK
        for (size_t j = 0; j < my_PageFrames.size(); j++)
            cout << my_PageFrames[j].first << " ";

        if (FaultNumber > FrameNumber && !flag)
            cout << "->" << EliminatePage[FaultNumber - FrameNumber - 1];

        cout << endl;
#endif
    }
    Report();
}
void Replace::Lfu(void)
{
    int next;
    int min;
    bool flag;
    int elim_index;
    InitSpace("LFU");

    //using a vector instead of a array
    vector<eclock> my_PageFrames;

    for (size_t i = 0; i < PageNumber; i++)
    {
        flag = false;
        next = ReferencePage[i];

        //find out if frame exists
        for (size_t j = 0; j < my_PageFrames.size(); j++)
        {
            //giving the aim a second chance
            if (my_PageFrames[j].first == next)
            {
                my_PageFrames[j].second++;
                flag = true;
                break;
            }
        }
        //if not exists,Fage error
        if (!flag)
        {
            //FaultNumber>=FrameNumber means elimination
            //serch for the min and elimiate it
            if (FaultNumber >= FrameNumber)
            {
                elim_index = 0;
                min = 3;
                assert(my_PageFrames.size() == FrameNumber);
                for (size_t j = 0; j < FrameNumber && min; j++)
                {
                    if (my_PageFrames[j].second < min)
                    {
                        min = my_PageFrames[j].second;
                        elim_index = j;
                    }
                }

                //if the elim one is not the first frame in queue,modify the frame before it
                if (elim_index > 0)
                {
                    for (int j = 0; j < elim_index; j++)
                    {
                        my_PageFrames[elim_index].second--;
                    }
                }
                EliminatePage[FaultNumber - FrameNumber] = my_PageFrames[elim_index].first;
                my_PageFrames.erase(my_PageFrames.begin() + elim_index);
            }
            eclock e = make_pair(next, 0);
            my_PageFrames.push_back(e);
            FaultNumber++;
        }
#ifdef CHECK
        for (size_t j = 0; j < my_PageFrames.size(); j++)
            cout << my_PageFrames[j].first << " ";

        if (FaultNumber > FrameNumber && !flag)
            cout << "->" << EliminatePage[FaultNumber - FrameNumber - 1];

        cout << endl;
#endif
    }
    Report();
}
void Replace::Mfu(void)
{
    int next;
    int min;
    bool flag;
    int elim_index;
    InitSpace("MFU");

    //using a vector instead of a array
    vector<eclock> my_PageFrames;

    for (size_t i = 0; i < PageNumber; i++)
    {
        flag = false;
        next = ReferencePage[i];

        //find out if frame exists
        for (size_t j = 0; j < my_PageFrames.size(); j++)
        {
            //giving the aim a second chance
            if (my_PageFrames[j].first == next)
            {
                my_PageFrames[j].second--;
                flag = true;
                break;
            }
        }
        //if not exists,Fage error
        if (!flag)
        {
            //FaultNumber>=FrameNumber means elimination
            //serch for the min and elimiate it
            if (FaultNumber >= FrameNumber)
            {
                elim_index = 0;
                min = 3;
                assert(my_PageFrames.size() == FrameNumber);
                for (size_t j = 0; j < FrameNumber && min; j++)
                {
                    if (my_PageFrames[j].second < min)
                    {
                        min = my_PageFrames[j].second;
                        elim_index = j;
                    }
                }

                //if the elim one is not the first frame in queue,modify the frame before it
                if (elim_index > 0)
                {
                    for (int j = 0; j < elim_index; j++)
                    {
                        my_PageFrames[elim_index].second--;
                    }
                }
                EliminatePage[FaultNumber - FrameNumber] = my_PageFrames[elim_index].first;
                my_PageFrames.erase(my_PageFrames.begin() + elim_index);
            }
            eclock e = make_pair(next, 0);
            my_PageFrames.push_back(e);
            FaultNumber++;
        }
#ifdef CHECK
        for (size_t j = 0; j < my_PageFrames.size(); j++)
            cout << my_PageFrames[j].first << " ";

        if (FaultNumber > FrameNumber && !flag)
            cout << "->" << EliminatePage[FaultNumber - FrameNumber - 1];

        cout << endl;
#endif
    }
    Report();
}
int main(int argc, char *argv[])
{
    Replace *vmpr = new Replace();
    vmpr->Lru();
    vmpr->Fifo();
    vmpr->Eclock();
    vmpr->Mfu();
    vmpr->Lfu();
    // vmpr->Clock();
    return 0;
}