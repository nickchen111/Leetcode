for (int subset=state; subset>0; subset=(subset-1)&state)
{
   DoSomething(subset);
}


// 我比較常用的寫法
int submask = mask;
while (submask) {// 空集合改true
   int remainging = submask ^ mask;
   // 枚舉子集的子集...
   submask = (submask - 1) & mask;
   // 如果是包含空集合
   if (submask == mask) break;
}
