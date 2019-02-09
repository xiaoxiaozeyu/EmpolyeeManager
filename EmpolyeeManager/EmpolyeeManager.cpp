/*定义职工（employee ）类，其中至少包括姓名、性别、工号、电话、所在科室和工资。*/
#include<iostream>
#include<cstring>
#include<fstream>
#include<stdlib.h>
using namespace std;
class employee
{
private:
	int m_Id;    //职工号
	float m_salary;    //工资
	char m_name[20];    //职工姓名
	char m_tel[14];     //电话
	char m_office[20];    //科室
	char m_sex[5];     //性别
public:
	employee() {}
	employee& operator =(employee &re)
	{
		strcpy(m_name, re.m_name);
		strcpy(m_tel, re.m_tel);
		strcpy(m_office, re.m_office);
		strcpy(m_sex, re.m_sex);
		m_Id = re.m_Id;
		m_salary = re.m_salary;
		return *this;
	}
	char *get_name()
	{
		return m_name;
	}
	char *get_office()
	{
		return m_office;
	}
	float get_salary()
	{
		return m_salary;
	}
	int get_ID()
	{
		return m_Id;
	}
	friend ostream& operator <<(ostream &os, const employee &re)
	{
		os << re.m_name << "\t\t" << re.m_sex << "\t\t" << re.m_Id << "\t\t" << re.m_tel << "\t\t" << re.m_office << "\t\t" << re.m_salary << endl;
		return os;
	}
	friend istream& operator >>(istream &is, employee &re)
	{
		is >> re.m_name >> re.m_sex >> re.m_Id >> re.m_tel >> re.m_office >> re.m_salary;
		return is;
	}
	~employee() {}
};

/* 2、输入功能：输入职工信息，并保存到文件中；*/

void AddEmployee()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::out | ios::app | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else {
		int len;
		cout << "请输入添加的职工数：";
		cin >> len;
		if (len > 0)
		{
			employee *emp = new employee[len];
			cout << "请输入职工的姓名、性别、工号、电话、所在科室和工资" << endl;
			for (int i = 0; i < len; i++)
			{
				cin >> emp[i];
				fs.write((char*)&emp[i], sizeof(emp[i]));
			}
			delete[]emp;
		}
	}
	fs.close();
	fs.clear();
}

/* 3、查询功能：1）能够根据工号精确查询职工信息；*/

void ReseachByID()
{

	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		int id, i;
		cout << "请输入你要查询的人的工号:";
		cin >> id;
		fs.seekg(0, ios::end);     //文件指针调到文件末尾
		int s = fs.tellg();        //计算文件大小
		int n = s / sizeof(employee);    //计算文件中职工人数
		fs.seekg(ios::beg);    //文件指针调到文件开头
		employee *e = new employee[n];
		employee temp;
		for (i = 0; i < n; i++)
			fs.read((char *)&e[i], sizeof(e[i]));

		int j = -1;
		for (i = 0; i < n; i++)
			if (id == e[i].get_ID())
				j = i;
		if (j == -1)
			cout << "无此职工号！" << endl;
		else
		{
			cout << "姓名       |    性别   |        工号        |     电话           |     科室     |       工资     " << endl;
			cout << "-----------|-----------|--------------------|--------------------|--------------|-------------" << endl;
			cout << e[j];
		}
		delete[] e;
	}
	fs.close();
	fs.clear();
}

/*3、查询功能：2）能够根据姓名、科室查询职工信息*/

void ReseachByNameAOffice()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		char name[20];
		char office[20];
		cout << "请输入你要查询的人的姓名:";
		cin >> name;
		cout << "请输入你要查询的人的科室:";
		cin >> office;
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		employee *e = new employee[n];
		employee temp;
		int i, j;
		for (i = 0; i < n; i++)
			fs.read((char *)&e[i], sizeof(e[i]));
		j = -1;
		for (i = 0; i < n; i++)
			if (strcmp(name, e[i].get_name()) == 0 && strcmp(office, e[i].get_office()) == 0)
				j = i;
		if (j == -1)
			cout << "无此职工！" << endl;
		else
		{
			cout << "姓名       |    性别   |        工号        |     电话           |     科室     |       工资     " << endl;
			cout << "-----------|-----------|--------------------|--------------------|--------------|-------------" << endl;
			cout << e[j];
		}
		delete[] e;
	}
	fs.close();
	fs.clear();
}

/*3、查询功能：3）分科室进行工资统计，计算各科室的平均工资*/

void AverSalaryByOffice()
{

	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		char office[20];
		cout << "请输入你要查询平均工资的科室:";
		cin >> office;
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		employee *e = new employee[n];
		employee temp;
		int i, j, count;
		for (i = 0; i < n; i++)
			fs.read((char *)&e[i], sizeof(e[i]));
		j = -1;
		count = 0;
		float sum = 0;
		for (i = 0; i < n; i++)
		{
			if (strcmp(office, e[i].get_office()) == 0)
			{
				j = i;
				sum = sum + e[i].get_salary();
				count++;
			}
		}
		if (j == -1)
			cout << "无此科室！" << endl;
		else
			cout << "科室" << e[j].get_office() << "的平均工资为:" << sum / count << endl;
		delete[] e;
	}
	fs.close();
	fs.clear();
}

/*4、根据职工的工资排序输出*/

void SortBySalary()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		int i;
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		if (n == 0)
			cout << "系统中无职工信息！" << endl;
		else
		{
			employee *e = new employee[n];
			employee temp;
			for (i = 0; i < n; i++)
				fs.read((char *)&e[i], sizeof(e[i]));
			for (int j = 0; j < n - 1; j++)    //冒泡排序
			{
				for (int k = 0; k < n - 1 - j; k++)
				{
					if (e[k].get_salary() > e[k + 1].get_salary())
					{
						temp = e[k];
						e[k] = e[k + 1];
						e[k + 1] = temp;
					}
				}
			}
			cout << "----------------------------------------按工资排序--------------------------------------------" << endl;
			cout << "姓名       |    性别   |        工号        |     电话           |     科室     |       工资     " << endl;
			cout << "-----------|-----------|--------------------|--------------------|--------------|-------------" << endl;
			for (i = 0; i < n; i++)
				cout << e[i];
			delete[] e;
		}
	}
	fs.close();
	fs.clear();
}

/* 5、根据工号修改职工信息*/

void ModEmployee()
{

	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::out | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		int id, i;
		cout << "输入你要修改的职工号:";
		cin >> id;
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		int j = -1;
		employee *e = new employee[n];
		for (i = 0; i < n; i++)
			fs.read((char *)&e[i], sizeof(e[i]));
		for (i = 0; i < n; i++)
		{
			if (id == e[i].get_ID())
				j = i;
		}
		if (j == -1)
			cout << "无此职工！" << endl;
		else
		{
			fs.seekp(sizeof(employee)*j);
			employee t;
			cout << "请输入修改职工的姓名、性别、工号、电话、所在科室和工资" << endl;
			cin >> t;
			fs.write((char *)&t, sizeof(employee));
			cout << "职工信息修改成功！" << endl;
		}
		delete[] e;
	}
	fs.close();
	fs.clear();
}

//浏览所有人员信息
void Show()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		if (n == 0)
			cout << "系统中无职工信息！" << endl;
		else
		{
			employee *e = new employee[n];
			cout << "----------------------------------------所有职工信息------------------------------------------" << endl;
			cout << "姓名       |    性别   |        工号        |     电话           |     科室     |       工资     " << endl;
			cout << "-----------|-----------|--------------------|--------------------|--------------|-------------" << endl;
			for (int i = 0; i < n; i++)
			{
				fs.read((char *)&e[i], sizeof(e[i]));
				cout << e[i];
			}
			delete[] e;
		}

	}
	fs.close();
	fs.clear();
}

/* 6、根据工号删除职工信息*/

void DelEmployee()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		if (n == 0)
			cout << "系统中无职工信息！" << endl;
		else
		{
			employee *e = new employee[n];
			int id, i, j;
			for (i = 0; i < n; i++)
			{
				fs.read((char *)&e[i], sizeof(e[i]));
			}
			fs.close();
			fs.clear();
			cout << "请输入要删除的职工号：";
			cin >> id;
			for (i = 0; i < n; i++)
			{
				j = -1;
				if (id == e[i].get_ID())
					j = i;
			}
			fs.open("employeeinfo.dat", ios::out | ios::trunc | ios::binary);
			for (i = 0; i < n; i++)
			{
				if (i == j)
					continue;
				else
				{
					fs.write((char *)&e[i], sizeof(e[i]));
				}
			}
			if (j == -1)
				cout << "无此职工！" << endl;
			else
				cout << "该职工已成功删除！" << endl;
			fs.close();
			fs.clear();
			delete[] e;
		}
	}
}

//菜单函数
void Meun()
{
	cout << "====================================== 职工工资管理系统 =======================================" << endl;
	cout << "||                                                                                           ||" << endl;
	cout << "||                              ——————————————                                 ||" << endl;
	cout << "||                             | * 1.添加职工信息          |                                 ||" << endl;
	cout << "||                             | * 2.工号查找职工          |                                 ||" << endl;
	cout << "||                             | * 3.姓名+科室查找职工     |                                 ||" << endl;
	cout << "||                             | * 4.各科室平均工资        |                                 ||" << endl;
	cout << "||                             | * 5.按工资对职工排序      |                                 ||" << endl;
	cout << "||                             | * 6.修改人员信息          |                                 ||" << endl;
	cout << "||                             | * 7.删除人员信息          |                                 ||" << endl;
	cout << "||                             | * 8.浏览所有人员信息      |                                 ||" << endl;
	cout << "||                             | * 0.关闭系统              |                                 ||" << endl;
	cout << "||                              ——————————————                                 ||" << endl;
	cout << "||                                                     Designed By ZeyuGuo                   ||" << endl;
	cout << "===============================================================================================" << endl;
	cout << "请输入选择(0-8)：";
}

//主函数
int main()
{

	char flag = 'n';
	while (flag == 'n' || flag == 'N')    //由y/n控制循环
	{
		Meun();
		int judge;
		cin >> judge;
		if (judge >= 0 && judge <= 8)
		{
			switch (judge)
			{
			case 0:
				cout << "是否退出系统(y/n):";
				cin >> flag;
				break;
			case 1:
				AddEmployee();
				break;
			case 2:
				ReseachByID();
				break;
			case 3:
				ReseachByNameAOffice();
				break;
			case 4:
				AverSalaryByOffice();
				break;
			case 5:
				SortBySalary();
				break;
			case 6:
				ModEmployee();
				break;
			case 7:
				DelEmployee();
				break;
			case 8:
				Show();
				break;
			default:
				break;
			}
		}
		else
			cout << "输入错误，请重新输入!" << endl;
		cout << "按任意键返回主菜单!" << endl;
		getchar();
		getchar();
		system("cls");
	}
	return 0;
}