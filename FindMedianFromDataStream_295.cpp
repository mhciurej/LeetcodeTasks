//https://leetcode.com/problems/find-median-from-data-stream/submissions/1268741890/

class MedianFinder {
    std::multiset<double> s;
    std::multiset<double>::iterator lhs;
    std::multiset<double>::iterator rhs;
public:
    MedianFinder() {}
    
    void addNum(double num) {
        if(s.empty())
        {
            s.insert(num);
            lhs = s.begin();
            rhs = s.begin();
            return;
        }
        double median = findMedian();
        s.insert(num);
        if(num < *lhs)
        {
            if(lhs == rhs)
            {
                lhs--;
            }
            else
            {
                rhs--;
            }
        }
        else if(num >= *rhs)
        {
            if(lhs == rhs)
            {
                rhs++;
            }
            else
            {
                lhs++;
            }
        }
        else if(lhs != rhs)
        {
            lhs++;
            rhs--;
        }
        else
        {
            rhs++;
        }

    }
    
    double findMedian() const {
        return ((*lhs) + (*rhs)) / 2;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */