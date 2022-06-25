#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3_sem2/PriorityQueue.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int redouble(int a) {
	a *= 2;
	return a;
}

bool positive(int a) {
	if (a < 11) {
		return true;
	}
	else {
		return false;
	}
}
int sum(int a, int b) {
	return a + b;
}

namespace UnitTestsLab3
{
	TEST_CLASS(UnitTestsLab3)
	{
	public:
		TEST_METHOD(BinTreeBasicMethods)
		{
			BinaryTree<int> sample1;
			BinaryTree<int> expected1{ 10 };
			sample1.Insert(10);
			Assert::IsTrue(sample1 == expected1, L"Insert method");
			BinaryTree<int> sample2{ 2,3,5,6,7,8 };
			BinaryTree<int> copy = sample2;
			Assert::IsTrue(sample2 == copy, L"Copy constructor");
			int a = 5;
			Assert::IsTrue(sample2.Find(5), L"Find method");
			copy.DeleteByValue(3);
			BinaryTree<int> expected2{ 6,2,7,5,8};
			Assert::IsTrue(copy == expected2, L"Value detele method");
			Assert::IsTrue(sample2.GetQuantity() == 6, L"Get quantity method");
		}
		TEST_METHOD(MapWhereReduceBT)
		{
			BinaryTree<int> sample1{ 2,3,5,6,7,8};
			BinaryTree<int>* sample2 = sample1.Map(redouble);
			BinaryTree<int> expected1{4,6,10,12,14,16 };
			Assert::IsTrue((* sample2) == expected1, L"Map method");
			BinaryTree<int>* sample3 = sample2->Where(positive);
			BinaryTree<int> expected2{ 4,6,10 };
			Assert::IsTrue(expected2 == (*sample3), L"Where method");
			int summary = sample1.Reduce(sum, 0);
			Assert::IsTrue(summary == 31, L"Reduce method");
			delete sample2;
			delete sample3;
		}
		TEST_METHOD(SubtreeAndSaveToSrting)
		{
			BinaryTree<double> sample1{ 2,3,5,6,7,8 };
			BinaryTree<double>* sample2 = sample1.GetSubtree(3);
			BinaryTree<double> expected2{ 3,2,5 };
			Assert::IsTrue((*sample2) == expected2, L"GetSubtree method");
			BinaryTree<int> sample3{ 2,3,5,6,7,8 };
			std::string lnr_walk = "((2)3[5]){6}[7[8]]";
			Assert::IsTrue(lnr_walk == sample3.SaveToString("LNR"), L"Save to string method(LNR)");
			std::string nlr_walk = "{6}(3(2)[5])[7[8]]";
			Assert::IsTrue(nlr_walk == sample3.SaveToString("NLR"), L"Save to string method(NLR)");
			std::string nrl_walk = "{6}[7[8]](3[5](2))";
			Assert::IsTrue(nrl_walk == sample3.SaveToString("NRL"), L"Save to string method(NRL)");
		}
		TEST_METHOD(PriorityQBasicMethods)
		{
			PriorityQueue<int> sample1{ 4,2,3,1 };
			sample1.Push(5);
			PriorityQueue<int> expected1{ 1,2,3,4,5 };
			Assert::IsTrue(sample1 == expected1, L"Push method");
			Assert::IsTrue(sample1.Top() == 5, L"Top method");
			sample1.Pop();
			PriorityQueue<int> expected2{ 1,2,3,4 };
			Assert::IsTrue(sample1 == expected2, L"Pop method");
			Assert::IsTrue(sample1.Size() == 4, L"Size method");
			PriorityQueue<double> sample2{ 2.72, 9.81, 3.14, 1.62, 1.41 };
			Assert::IsTrue(sample2.Find(3.14), L"Find method(t)");
			Assert::IsFalse(sample2.Find(0.57), L"Find method(f)");
		}
		TEST_METHOD(MapWhereReducePQ)
		{
			PriorityQueue<int> sample1{ 1,5,9,11,7,3 };
			PriorityQueue<int> *sample2 = sample1.Map(redouble);
			PriorityQueue<int> expected1{ 2,6,10,14,18,22 };
			Assert::IsTrue(*sample2 == expected1, L"Map method");
			PriorityQueue<int>* sample3 = expected1.Where(positive);
			PriorityQueue<int> expected2{ 2,6,10 };
			Assert::IsTrue(*sample3 == expected2, L"Where method");
			Assert::IsTrue(sample1.Reduce(sum, 0) == 36, L"Reduce method");
			delete sample2;
			delete sample3;
		}
		TEST_METHOD(GetSubqueue)
		{
			PriorityQueue<int> sample1{ 5,3,6,1,8,9,4,7 };
			PriorityQueue<int>* sample2 = sample1.GetSubqueue(3, 5);
			PriorityQueue<int> expected1{ 5,6,7 };
			Assert::IsTrue(*sample2 == expected1, L"Subqueue method");
			delete sample2;
		}
		TEST_METHOD(Merge) {
			PriorityQueue<int> sample1{ 5,3,6,1,8 };
			PriorityQueue<int> sample2{ 9,7,2 };
			PriorityQueue<int>* sample3 = sample1.Merge(sample2);
			PriorityQueue<int> expected{ 1,2,3,5,6,7,8,9 };
			Assert::IsTrue(expected == *sample3, L"Merge method");
			delete sample3;
			PriorityQueue<int> sample4;
			PriorityQueue<int>* sample5 = sample4.Merge(sample2);
			PriorityQueue<int> expected1{ 7,9,2 };
			Assert::IsTrue(expected1 == *sample5, L"Merge method(2)");
		}
		TEST_METHOD(IfSubqueue)
		{
			PriorityQueue<int> sample1{ 1,8,3,2,4,6,7,9,5 };
			PriorityQueue<int> sample2{ 6,5,7 };
			Assert::IsTrue(sample1.IfSubqueue(sample2), L"IfSubqueue method");
			PriorityQueue<int> sample3;
			Assert::IsTrue(sample1.IfSubqueue(sample3), L"Empty subqueue");
			Assert::IsTrue(sample1.IfSubqueue(sample1), L"Equal queues");
		}
	};
}
