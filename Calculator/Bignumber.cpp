#include "Bignumber.h"

Bignumber bignumber;
void Bignumber::updatewithinput1()
{
	for (int i = 0; i < 4; i++)
	{
		if (button1[i] && i == 0)      bignumberadd(), button1[i] = false;
		else if (button1[i] && i == 1) bignumbersubtract(), button1[i] = false;
		else if (button1[i] && i == 2) bignumbermuit(), button1[i] = false;
		else if (button1[i] && i == 3) bignumberdiv(), button1[i] = false;
	}

	MOUSEMSG m;
	while (MouseHit())	// ����Ƿ��������Ϣ
	{
		m = GetMouseMsg();

		Window_Message.windowmessage(m); //�ƶ�����

		if (m.x > 5 && m.x < 40 && m.y > 30 && m.y < 50)	// ����
		{
			transformation.help[0] = true;
			if (m.uMsg == WM_LBUTTONUP)
			{
				transformation.software[0] = -1;
				transformation.software[2] = 3;
			}
		}
		else transformation.help[0] = false;

		for (int i = 0; i < 4; i++)
		{
			if (m.x > i * 102 && m.x < 98 + 102 * i && m.y>550 && m.y < 598)
			{
				if (m.uMsg == WM_LBUTTONUP)
				{
					button1[i] = true;
					for (int j = 0; j < 4; j++)
						if (j != i)button1[j] = false;
				}
			}

		}
		
		if (m.uMsg == WM_MOUSEWHEEL)
		{
			if (m.wheel < 0)
				transformation.fly += 10;
			else
				transformation.fly -= 10;
		}
	}
	double len = (_tcslen(s6) / 43.0 + 1)*19.2307692308 - 19.2307692308;	// �ַ�������
	
	if (len < 500)
	{
		if (transformation.fly > 0)
			transformation.fly -= transformation.fly / 3;
	}
	else
	{
		if (transformation.fly + 500 >= len)
			transformation.fly -= (int)abs(transformation.fly + 500 - len) / 3;
	}
	if (transformation.fly < 0)
		transformation.fly += -(transformation.fly / 3);
	Sleep(option.Performance);
}

void Bignumber::showscreen1()
{
	BeginBatchDraw();	                                        // ��ʼ������ͼ
	setfillstyle(BS_SOLID);
	
	switch(option.WindowStyle)
	{
	case 0:  conversion.Setcolor(0, 406, 60, 600); break;
	case 1:  conversion.Setcolor(0, 406, 60, 600, RGB(180, 180, 180)); break;
	default: conversion.changecolor(0, 406, 60, 600); break;
	}                   

	IMAGE black = MyLoadImage.setimage(406, 540, RGB(0, 0, 0));	// ���û�ͼ
	MyPutimage.my_putimage(0, 60, &black, RGB(255, 255, 255), 0, 1, 30, 0);

	settextstyle(20, 0, _T("΢���ź�"), false, false, 900, false, false, false);
	settextcolor(WHITE);
	RECT r = { 9,60 - transformation.fly ,400,100000 - transformation.fly };
	drawtext(s6, &r, DT_WORDBREAK);

	switch (option.WindowStyle)
	{
	case 0:  conversion.Setcolor(0, 406, 0, 60); break;
	case 1:  conversion.Setcolor(0, 406, 0, 60, RGB(180, 180, 180)); break;
	default: conversion.changecolor(0, 406, 0, 60); break;
	}                

	black = MyLoadImage.setimage(406, 61, RGB(0, 0, 0));	// ���û�ͼ
	MyPutimage.my_putimage(0, 0, &black, RGB(255, 255, 255), 0, 1, 30, 0);

	switch (option.WindowStyle)
	{
	case 0:  conversion.Setcolor(0, 406, 550, 600); break;
	case 1:  conversion.Setcolor(0, 406, 550, 660, RGB(180, 180, 180)); break;
	default: conversion.changecolor(0, 406, 550, 600); break;
	}                  

	Window_Message.GetFunctionName(_T("�߾�������"));
	
	for (int i = 0; i < 4; i++)
	{
		if (!button1[i])
		{
			IMAGE blacks = MyLoadImage.setimage(100, 50,RGB(0, 0, 0));	    // ���û�ͼ
			MyPutimage.my_putimage(i * 102, 548, &blacks, RGB(255, 255, 255), 0, 1, 80, 0);
		}
		else
		{
			IMAGE green = MyLoadImage.setimage(100, 50,RGB(14,220,231));	// ���û�ͼ
			MyPutimage.my_putimage(i * 102, 548, &green, RGB(255, 255, 255), 0, 1, 80, 0);
		}
	}
	settextstyle(40, 0, _T("Consolas"));
	settextcolor(WHITE);
	outtextxy(40, 550, '+');
	outtextxy(244, 550, _T("��"));
	outtextxy(346, 550, _T("��"));
	settextstyle(40, 25, _T("Consolas"));
	outtextxy(142, 550, '-');
	
	EndBatchDraw();
}
//��ʼ��
void Bignumber::memsenumber()
{
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	memset(s4, 0, sizeof(s4));
	memset(s5, 0, sizeof(s5));
	memset(s6, 0, sizeof(s6));
}
/**********************************************�ӷ�******************************************/
//�������ּӼ�һ
void Bignumber::LsJJ(MyChar *s4, bool t)
{
	int ls[1000] = { 0 };
	int g = (int)_tcslen(s4);
	for (int i = 0; i < g; i++)
		ls[i] = s4[i] - '0';
	memset(s4, 0, sizeof(s4));

	if (!t)
	{
		ls[g - 1]--;
		for (int i = g - 1; i > 0; i--)
		{
			if (ls[i] < 0)
			{
				ls[i] += 10;
				ls[i - 1]--;
			}
		}
		bool flag(false);
		int m = 0;
		for (int i = 0; i < g; i++)
		{
			if (ls[i])flag = true;
			if (flag)s4[m++] = ls[i] + '0';
		}
		s4[m] = '\0';
	}
	else
	{
		ls[g - 1]++;
		for (int i = g - 1; i > 0; i--)
		{
			if (ls[i] > 9)
			{
				ls[i] -= 10;
				ls[i - 1]++;
			}
		}
		if (ls[0] > 9)
		{
			ls[0] -= 10;
			s4[0] = '1';
			int m;
			for (m = 1; m <= g; m++)
			{
				s4[m] = ls[m - 1] + '0';
			}
			s4[m] = '\0';
		}
	}

}


MyChar* Bignumber::numbersubx(MyChar *ss, MyChar *ss1)
{
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	memset(s6, 0, sizeof(s6));
	int alen = (int)_tcslen(ss), blen = (int)_tcslen(ss1);
	int sum = max(alen, blen);
	for (int i = 0; i < sum; i++)
	{
		if (alen > i)a[i] = ss[i] - '0';
		if (blen > i)b[i] = ss1[i] - '0';
	}
	int f(0);
	if (_tcscmp(ss, ss1) < 0)f = -1;
	if (f == -1)for (int i = 0; i < sum; i++)c[i] = b[i] - a[i];
	else for (int i = 0; i < sum; i++)c[i] = a[i] - b[i];

	for (int i = sum - 1; i >= 0; i--)
		if (c[i] < 0) c[i] += 10, c[i - 1]--;

	int flag(0), n(0), j(0);
	if (f == -1)s6[j++] = '-';	                       // �����һ��һ�������Ϊ����
	for (int i = 0; i < sum; i++)
	{
		n++;
		if (n % 43 == 0)s6[j++] = '\n';
		s6[j++] = c[i] + '0';
	}
	return s6;
}

MyChar* Bignumber::numbersub(MyChar *ss, MyChar *ss1)
{
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	memset(s6, 0, sizeof(s6));
	int alen = (int)_tcslen(ss), blen = (int)_tcslen(ss1);
	int sum = max(alen, blen);
	for (int i = 0; i < sum; i++)
	{
		if (alen > i)a[i] = ss[alen - 1 - i] - '0';
		if (blen > i)b[i] = ss1[blen - 1 - i] - '0';
	}
	int f(0);
	if (alen < blen || (alen == blen && _tcscmp(ss, ss1) < 0))f = -1;
	if (f == -1)for (int i = 0; i < sum; i++)c[i] = b[i] - a[i];
	else for (int i = 0; i < sum; i++)c[i] = a[i] - b[i];

	for (int i = 0; i < sum; i++)
		if (c[i] < 0) c[i] += 10, c[i + 1]--;
	int flag(0), n(0), j(0);
	
	if (f == -1)s6[j++] = '-';                       	// �����һ��һ�������Ϊ����
	for (int i = sum; i >= 0; i--)
	{
		if (c[i])flag = 1;
		if (flag == 1)
		{
			n++;
			if (n % 43 == 0)s6[j++] = '\n';
			s6[j++] = c[i] + '0';
		}
	}
	if (!flag)s6[j++] = 0 + '0';
	return s6;
}

// �߾��ȼӷ�
MyChar* Bignumber::numberadd(MyChar *ss, MyChar *ss1)
{
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	memset(s6, 0, sizeof(s6));
	int alen = (int)_tcslen(ss), blen = (int)_tcslen(ss1);
	int max = alen > blen ? alen : blen;
	for (int i = 0; i <= max; i++)
	{
		if (alen > i&&blen > i)c[i] = ss[alen - 1 - i] - '0' + ss1[blen - 1 - i] - '0';
		if (alen <= i && blen > i)c[i] = ss1[blen - 1 - i] - '0';
		if (alen > i&&blen <= i)c[i] = ss[alen - 1 - i] - '0';
	}
	for (int i = 0; i <= max; i++)
		c[i + 1] += c[i] / 10, c[i] %= 10;
	int flag(0), j(0), n(0);
	for (int i = max; i >= 0; i--)
	{
		if (c[i] != 0)flag = 1;
		if (flag == 1)
		{
			n++;
			if (n % 43 == 0)s6[j++] = '\n';
			s6[j++] = c[i] + '0';
		}
	}
	if (!flag)s6[j++] = 0 + '0';
	return s6;
}

// �߾��ȼӷ�
MyChar* Bignumber::numberaddx(MyChar *ss, MyChar *ss1)
{
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	memset(s6, 0, sizeof(s6));

	int alen = (int)_tcslen(ss), blen = (int)_tcslen(ss1);
	int max = alen > blen ? alen : blen;
	for (int i = 0; i <= max; i++)
	{
		if (alen > i&&blen > i)c[i] = ss[i] - '0' + ss1[i] - '0';
		if (alen <= i && blen > i)c[i] = ss1[i] - '0';
		if (alen > i&&blen <= i)c[i] = ss[i] - '0';
	}
	for (int i = max; i > 0; i--)
		c[i - 1] += c[i] / 10, c[i] %= 10;

	int j(0), n(0);
	if (c[0] >= 10)
	{
		s6[j++] = '.';
		c[0] %= 10;
	}
	for (int i = 0; i < max; i++)
	{
		n++;
		if (n % 43 == 0)s6[j++] = '\n';
		s6[j++] = c[i] + '0';
	}
	return s6;
}

// �߾��ȼӷ�
void Bignumber::bignumberadd()
{
	memsenumber();
	InputBox(s4, 100000, _T("ע�����������ȷ�����֣���Ҫ���س�"), _T("�������һ����"), _T(""), 400, 300);
	InputBox(s5, 100000, _T("ע�����������ȷ�����֣���Ҫ���س�"), _T("������ڶ�����"), _T(""), 400, 300);

	int alen = (int)_tcslen(s4), blen = (int)_tcslen(s5);
	bool fu = false, fu1 = false, fu2 = false;	                   // �ж��Ƿ�Ϊ����
	if (s4[0] == '-')
	{
		fu1 = true;
		for (int i = 0; i < alen; i++)	                           // ȥ������
			s4[i] = s4[i + 1];
	}
	if (s5[0] == '-')
	{
		fu2 = true;
		for (int i = 0; i < blen; i++)	                           // ȥ������
			s5[i] = s5[i + 1];
	}

	int lena = 0, lenb = 0;                    	                   // ��¼С��λ��
	MyChar *p = NULL, *q = NULL;
	p = _tcschr(s4, '.');	                                       // �ж��Ƿ���С��
	q = _tcschr(s5, '.');
	alen = (int)_tcslen(s4), blen = (int)_tcslen(s5);
	MyChar s7[10000] = { '0' }, s8[10000] = { '0' };
	if (p - s4 >= 1)
	{
		lena = alen - (int)(p - s4 + 1); 	                       // �����С��,����С����λ��
		int m = 0;
		for (int i = (int)(p - s4 + 1); i < alen; i++) 	           // С������
			s7[m++] = s4[i];
		s7[m] = '\0';
		s4[p - s4] = '\0';	                                       // ��������
	}
	if (q - s5 >= 1)
	{
		lenb = blen - (int)(q - s5 + 1); 	                       // �����С��
		int m = 0;
		for (int i = (int)(q - s5 + 1); i < blen; i++) 	           // С������
			s8[m++] = s5[i];
		s8[m] = '\0';
		s5[q - s5] = '\0';	                                       // ��������
	}

	if (fu1 && !fu2)	                                           // �����һ�����Ǹ������ڶ�����������
	{
		if (p - s4 >= 1 || q - s5 >= 1)	                           // ��С��
		{
			if (_tcslen(s5) > _tcslen(s4) || _tcslen(s5) == _tcslen(s4) && _tcscmp(s5, s4) > 0 ||
				_tcscmp(s4, s5) == 0 && _tcscmp(s8, s7) > 0)       // �����ȸ�����
			{
				_tcscpy_s(s4, numbersub(s5, s4));
				_tcscpy_s(s5, numbersubx(s8, s7));
			}
			else
			{
				fu = true;
				_tcscpy_s(s4, numbersub(s4, s5));
				_tcscpy_s(s5, numbersubx(s7, s8));
			}

			if (s5[0] == '-')
			{
				LsJJ(s4, false);                                   //�������ּ�һ���һ
				b[0] = 1, a[0] = 0;
				int k = (int)_tcslen(s5);
				for (int i = 1; i < k; i++)	                       // ת��Ϊ����
				{
					a[i] = s5[i] - '0';
					b[i] = 0;
				}
				for (int i = 0; i < k; i++)	                       // ��λ����
					c[i] = b[i] - a[i];

				for (int i = k - 1; i > 0; i--)	                   // ��λ
					if (c[i] < 0)c[i] += 10, c[i - 1]--;

				if (fu)
				{
					_tcscpy_s(s6, _T("-"));
					_tcscat_s(s6, s4);
					memset(s4, 0, sizeof(s4));
					for (int i = 1; i < k; i++)
						s4[i - 1] = c[i] + '0';
					_tcscat_s(s6, _T("."));
					_tcscat_s(s6, s4);	                           // С������
				}
				else
				{
					_tcscpy_s(s6, s4);	                           // ��������
					memset(s4, 0, sizeof(s4));
					for (int i = 1; i < k; i++)
						s4[i - 1] = c[i] + '0';
					_tcscat_s(s6, _T("."));
					_tcscat_s(s6, s4);	// С������
				}
			}
			else
			{
				if (fu)
				{
					_tcscpy_s(s6, _T("-"));
					_tcscat_s(s6, s4);
					_tcscat_s(s6, _T("."));
					_tcscat_s(s6, s5);	                           // С������
				}
				else
				{
					_tcscpy_s(s6, s4);	                           // ��������
					_tcscat_s(s6, _T("."));
					_tcscat_s(s6, s5);	                           // С������
				}
			}
		}
		else
			numbersub(s5, s4);
	}
	else if (!fu1 && fu2)	                                       // ����������Ǹ�������һ����������
	{
		if (p - s4 >= 1 || q - s5 >= 1)	                           // ��С��
		{
			if (_tcslen(s4) > _tcslen(s5) || _tcslen(s5) == _tcslen(s4) && _tcscmp(s4, s5) > 0 ||
				_tcscmp(s4, s5) == 0 && _tcscmp(s7, s8) > 0)	   // �����ȸ�����
			{
				_tcscpy_s(s4, numbersub(s4, s5));
				_tcscpy_s(s5, numbersubx(s7, s8));
			}
			else
			{
				fu = true;
				_tcscpy_s(s4, numbersub(s5, s4));
				_tcscpy_s(s5, numbersubx(s8, s7));
			}
			if (s5[0] == '-')
			{
				LsJJ(s4, false);                                   //�������ּ�һ���һ
				b[0] = 1, a[0] = 0;
				int k = (int)_tcslen(s5);
				for (int i = 1; i < k; i++)	                       // ת��Ϊ����
				{
					a[i] = s5[i] - '0';
					b[i] = 0;
				}
				for (int i = 0; i < k; i++)                        // ��λ����
					c[i] = b[i] - a[i];

				for (int i = k - 1; i > 0; i--)	                   // ��λ
					if (c[i] < 0)c[i] += 10, c[i - 1]--;

				if (fu)
				{
					_tcscpy_s(s6, _T("-"));
					_tcscat_s(s6, s4);
					memset(s4, 0, sizeof(s4));
					for (int i = 1; i < k; i++)
						s4[i - 1] = c[i] + '0';
					_tcscat_s(s6, _T("."));
					_tcscat_s(s6, s4);	                           // С������
				}
				else
				{
					_tcscpy_s(s6, s4);	                           // ��������
					memset(s4, 0, sizeof(s4));
					for (int i = 1; i < k; i++)
						s4[i - 1] = c[i] + '0';
					_tcscat_s(s6, _T("."));
					_tcscat_s(s6, s4);	                           // С������
				}
			}
			else
			{
				if (fu)
				{
					_tcscpy_s(s6, _T("-"));
					_tcscat_s(s6, s4);
					_tcscat_s(s6, _T("."));
					_tcscat_s(s6, s5);	                          // С������
				}
				else
				{
					_tcscpy_s(s6, s4);	                          // ��������
					_tcscat_s(s6, _T("."));
					_tcscat_s(s6, s5);	                          // С������
				}
			}
		}
		else
			numbersub(s4, s5);
	}
	else	                                                     // ������ͬ����ͬ��
	{
		if (p - s4 >= 1 || q - s5 >= 1)                     	 // ��С��
		{
			_tcscpy_s(s4, numberadd(s4, s5));
			_tcscpy_s(s5, numberaddx(s7, s8));
			if (s5[0] == '.')
			{
				LsJJ(s4, true);                                  //�������ּ�һ���һ
				if (fu1&&fu2)	                                 // ͬΪ����
				{
					_tcscpy_s(s6, _T("-"));
					_tcscat_s(s6, s4);
					_tcscat_s(s6, s5);
				}
				else
				{
					_tcscpy_s(s6, s4);
					_tcscat_s(s6, s5);
				}
			}
			else
			{
				if (fu1&&fu2)
				{
					_tcscpy_s(s6, _T("-"));
					_tcscat_s(s6, s4);
					_tcscat_s(s6, _T("."));
					_tcscat_s(s6, s5);
				}
				else
				{
					_tcscpy_s(s6, s4);
					_tcscat_s(s6, _T("."));
					_tcscat_s(s6, s5);
				}
			}
		}
		else// û��С��
		{
			if (fu1&&fu2)	// ͬΪ��
			{
				_tcscpy_s(s4, numberadd(s4, s5));
				_tcscpy_s(s6, _T("-"));
				_tcscat_s(s6, s4);
			}
			else
				numberadd(s4, s5);
		}
	}
}

/*****************************************����********************************************************/
void Bignumber::bignumbersubtract()	// �߾��ȼ���
{
	memsenumber();
	InputBox(s4, 100000, _T("ע�������������������������Ҳ��Ҫ���س�"), _T("�������һ����"), _T(""), 400, 300);
	InputBox(s5, 100000, _T("ע�������������������������Ҳ��Ҫ���س�"), _T("������ڶ�����"), _T(""), 400, 300);
	int alen = (int)_tcslen(s4), blen = (int)_tcslen(s5);
	int sum = max(alen, blen);
	for (int i = 0; i < sum; i++)
	{
		if (alen > i)a[i] = s4[alen - 1 - i] - '0';
		if (blen > i)b[i] = s5[blen - 1 - i] - '0';
	}
	int f(0);
	if (alen < blen || (alen == blen && _tcscmp(s4, s5) < 0))f = -1;
	if (f == -1)for (int i = 0; i < sum; i++)c[i] = b[i] - a[i];
	else for (int i = 0; i < sum; i++)c[i] = a[i] - b[i];

	for (int i = 0; i < sum; i++)
		if (c[i] < 0) c[i] += 10, c[i + 1]--;
	int flag(0), n(0), j(0);
	if (f == -1)s6[j++] = '-';	// �����һ��һ�������Ϊ����
	for (int i = sum; i >= 0; i--)
	{
		if (c[i])flag = 1;
		if (flag == 1)
		{
			n++;
			if (n % 43 == 0)s6[j++] = '\n';
			s6[j++] = c[i] + '0';
		}
	}
	if (!flag)s6[j++] = 0 + '0';
}


/***********************************�˷�**********************************/
void Bignumber::bignumbermuit()	// �߾��ȳ˷�
{
	memsenumber();
	InputBox(s4, 100000, _T("ע�����������ȷ������,��Ҫ���س�"), _T("�������һ����"), _T(""), 400, 300);
	InputBox(s5, 100000, _T("ע�����������ȷ������,��Ҫ���س�"), _T("������ڶ�����"), _T(""), 400, 300);

	int alen = (int)_tcslen(s4), blen = (int)_tcslen(s5);
	bool fu1 = false, fu2 = false;	    // �ж��Ƿ�Ϊ����
	if (s4[0] == '-')
	{
		fu1 = true;
		for (int i = 0; i < alen; i++)	// ȥ������
			s4[i] = s4[i + 1];
	}
	if (s5[0] == '-')
	{
		fu2 = true;
		for (int i = 0; i < blen; i++)	// ȥ������
			s5[i] = s5[i + 1];
	}

	int lena = 0, lenb = 0;	            // ��¼С��λ��
	MyChar *p = NULL, *q = NULL;
	p = _tcschr(s4, '.');	            // �ж��Ƿ���С��
	q = _tcschr(s5, '.');
	alen = (int)_tcslen(s4), blen = (int)_tcslen(s5);
	if (p - s4 >= 1)
	{
		lena = (int)(alen - (p - s4 + 1)); 	        // �����С��
		for (int i = (int)(p - s4); i < alen; i++)	// ȥ��С����
			s4[i] = s4[i + 1];
	}
	if (q - s5 >= 1)
	{
		lenb = (int)(blen - (q - s5 + 1));       	// �����С��
		for (int i = (int)(q - s5); i < blen; i++)	// ȥ��С����
			s5[i] = s5[i + 1];
	}

	alen = (int)_tcslen(s4);
	blen = (int)_tcslen(s5);
	
	int sum = max(alen, blen);
	for (int i = 0; i < sum; i++)
	{
		if (alen > i)a[i] = s4[alen - i - 1] - '0';
		if (blen > i)b[i] = s5[blen - i - 1] - '0';
	}
	for (int i = 0; i < alen; i++)
		for (int j = 0; j < blen; j++)
			c[i + j] += a[i] * b[j];
	for (int k = 0; k < alen + blen; k++)
		c[k + 1] += c[k] / 10, c[k] %= 10;
	int flag(0), n(0), j(0);
	if (!fu1&&fu2 || fu1 && !fu2)s6[j++] = '-';	// �����һ��һ�������Ϊ����
	for (int k = alen + blen - 1; k >= 0; k--)
	{
		if (c[k] || k == lena + lenb)flag = 1;	// ���ǰ��û��������ǳ���С���㣬flag Ϊ��
		if (flag == 1) {
			n++;
			if (n % 43 == 0)s6[j++] = '\n';
			if (k + 1 == lena + lenb)s6[j++] = '.';
			s6[j++] = c[k] + '0';
		}
	}
	if (!flag)s6[j++] = 0 + '0';
}


int cf(int *a, int *b, int lena, int lenb)
{
	if (lena < lenb)return -1;
	if (lena == lenb)	              // �ж� p1 > p2
	{
		for (int i = lena - 1; i >= 0; i--)
		{
			if (a[i] > b[i])          // ������������������������
				break;
			else if (a[i] < b[i]) 	  // ���򷵻� -1
				return -1;
		}
	}

	for (int i = 0; i < lena; i++)	 // ���������
	{
		a[i] -= b[i];
		if (a[i] < 0)a[i + 1]--, a[i] += 10;
	}
	for (int i = lena; i >= 0; i--)	 // ���س����������λ��
		if (a[i])
			return(i + 1);
	return 0;
}


/****************************************����***********************************/
void Bignumber::bignumberdiv()	// �߾��ȳ���
{
	memsenumber();
	InputBox(s4, 100000, _T("ע�������������������������Ҳ��Ҫ���س�"), _T("�������һ����"), _T(""), 400, 300);
	InputBox(s5, 100000, _T("ע�������������������������Ҳ��Ҫ���س�"), _T("������ڶ�����"), _T(""), 400, 300);
	int lena = (int)_tcslen(s4), lenb = (int)_tcslen(s5), sum = lena;
	if (lena < lenb)
	{ 
		s6[0] = '0';
		return; 
	}

	int wsc = lena - lenb;	            // ��������λ����
	for (int i = lena - 1; i >= 0; i--)	// �ֱ����������
	{
		a[i] = s4[lena - 1 - i] - '0';
		if (wsc - 1 - i < 0)b[i] = s5[lenb - 1 - i + wsc] - '0';
	}
	lenb = lena;
	int k;
	for (int i = 0; i <= wsc; i++)
		while ((k = cf(a, b + i, lena, lenb - i)) >= 0)	// �������ص�ֵ��ʾĿǰ��������λ��
			lena = k, c[wsc - i]++;
	int flag(0), n(0), j(0);
	for (int i = sum; i >= 0; i--)
	{
		if (c[i])flag = 1;
		if (flag == 1)
		{
			n++;
			if (n % 43 == 0)s6[j++] = '\n';
			s6[j++] = c[i] + '0';
		}
	}
	if (!flag)s6[j++] = 0 + '0';
}

void Bignumber::BignumberFuction(int &k)
{
	while (true)
	{
		updatewithinput1();
		showscreen1();
		if (k != transformation.software[0] + 1) break;
		Sleep(option.Performance);     // ��ʱ
	}
}