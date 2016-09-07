#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace Thread
{

template<typename T>
class ThreadSafeQueue
{
public:

    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue(){  startQueue(); }

    void enque(const T& e)
    {

        std::unique_lock<std::mutex> lock(_mu);
        _queue.push(e);
        _cond.notify_one();
        lock.unlock();
    }

    void dequeue(T& e)
    {
         std::unique_lock<std::mutex> lock(_mu);
         while(empty() && !_stop)
         {
             _cond.wait(lock);
         }

         if(!_stop)
         {
             e = _queue.front();
             _queue.pop();
         }
    }

    void stopQueue()
    {
        _stop = true;
        _cond.notify_all();
    }

    void startQueue()
    {
        _stop = false;
    }

    bool empty() const
    {
        return _queue.empty();
    }



private:



    std::queue<T> _queue;
    std::mutex _mu;

    std::condition_variable _cond;
    std::atomic_bool _stop;
};

}

#endif // THREADSAFEQUEUE_H
