void  solve(vector<int> vecFactor,int iSum,vector<vector<int> >& vecOutPut,vector<int>& vecResult)
{

	int iResult;
	if (vecFactor.size()==0)
	{
		if (iSum==0)
		{
			vecOutPut.push_back(vecResult);
		}	
	}
	else
	{
		int iFactor=vecFactor.front();
		vecFactor.erase(vecFactor.begin());
		if (iFactor==0)
		{
			return ;
		}

		for (int i = 0; i <=iSum/iFactor; i++) 
		{  
			iResult=i;		
			vecResult.push_back(iResult);
			solve(  vecFactor, iSum-iResult*iFactor, vecOutPut, vecResult);
			vecResult.pop_back();
		}  
	}
}
BOOL solve(vector<int> vecFactor,int iSum,vector<vector<int> >& vecOutPut)
{

	vector<int> vecResult;
	solve( vecFactor, iSum, vecOutPut, vecResult);
	return vecOutPut.size()>0;
}
int main()
{
	 
	int a[]={10,20,5,10};
	vector<int> vecFactor(a,a+4);
	int iSum=50;
	vector<vector<int> > vecOutPut;
	vector<int> vecResult;
	solve(vecFactor,iSum,vecOutPut);
}
