#pragma once
#include <object/base_obj.h>
using namespace cpy::object;
// 一级命名空间   namespace pi
namespace cpy
{
    // 一级命名空间   namespace pi
    namespace evaluator
    {
        class Environment
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Environment();
            // 带参构造函数
            Environment(const std::shared_ptr<Environment> &outer);

            /* 析构函数 */
            ~Environment() = default;

            /* 公有成员函数 */
            void set(const std::string &name, const std::shared_ptr<Object> &value); // 环境变量设置函数
            std::shared_ptr<Object> get(const std::string &name);                    // 环境变量获取函数
            bool isExist(const std::string &name);                                   // 环境变量存在判断函数
            void remove(const std::string &name);                                    // 环境变量删除函数
            void clear();                                                            // 环境变量清空函数

        private:
            /* 私有成员变量 */
            std::shared_ptr<Environment> outer;                             // 外层环境指针
            std::unordered_map<std::string, std::shared_ptr<Object>> store; // 存储环境变量的map
        };
    }
}