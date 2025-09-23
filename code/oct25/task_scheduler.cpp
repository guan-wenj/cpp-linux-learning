//
// Created by guan on 2025/9/23.
//
#include <print>
#include <vector>
#include <memory>
#include <functional>

class Task {
public:
    virtual ~Task() = default;
    virtual void execute()=0;
};

class LambdaTask : public Task {
    std::function<void()> func_;
public:
    explicit LambdaTask(std::function<void()> func):func_(std::move(func)){}
    void execute() override {
        func_();
    }
};

class Scheduler {
    size_t max_tasks_;
    std::vector<std::unique_ptr<Task>> tasks_;
    std::vector<std::unique_ptr<Task>> tasks_cache_;
public:
    explicit Scheduler(size_t max_tasks):max_tasks_(max_tasks){}
    size_t task_count() const { return tasks_.size(); }
    bool is_full() const { return tasks_.size() == max_tasks_; }
    void add_task(std::unique_ptr<Task> task) {
        if (!is_full()) {
            tasks_.emplace_back(std::move(task));
        }else {
            tasks_cache_.emplace_back(std::move(task));
        }
    }
    void add_task(std::function<void()> func) {
        add_task(std::make_unique<LambdaTask>(std::move(func)));
    }

    void executeAll() {
        for (auto& task : tasks_) {
            task->execute();
        }
        tasks_.clear();
        size_t transfer_count = std::min(max_tasks_, tasks_cache_.size());
        for (size_t i = 0; i < transfer_count; ++i) {
            // 从缓存前端移动任务到主队列（缓存通常按添加顺序处理）
            tasks_.emplace_back(std::move(tasks_cache_[i]));
        }
        // 移除缓存中已被转移的任务（关键修复）
        tasks_cache_.erase(tasks_cache_.begin(), tasks_cache_.begin() + transfer_count);
    }
};

void testSchedulerWithSmartPtr() {
    Scheduler scheduler(100); // 假设最大100个任务
    for (int i = 0; i < 1000; ++i) {
        scheduler.add_task([i]() {
            // 任务内容，例如打印日志
            std::println("task is {}",i);
        });

        // 定期执行任务
        if (scheduler.is_full()) {
            scheduler.executeAll();
        }
    }
    // 执行剩余任务
    scheduler.executeAll();
}

int main() {
    testSchedulerWithSmartPtr();
}