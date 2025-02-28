#pragma once
#include <object/base_obj.h>
#include <ast/identifier.h>
#include <ast/block.h>
#include <evaluator/environment.h>
#include <object/hashable.h>
namespace cpy
{
    namespace object
    {
        class Function : public Object, public Hashable
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Function();
            // 带参构造函数
            Function(const std::string &name, const std::vector<std::shared_ptr<ast::Identifier>> &parameters, const std::unordered_map<std::string, std::shared_ptr<ast::Expression>> &defaults, const std::shared_ptr<ast::Block> &body, const std::shared_ptr<evaluator::Environment> &env);

            /* 析构函数 */
            ~Function() = default;

            /* 公有成员函数 */
            virtual void init(const std::string &name, const std::vector<std::shared_ptr<ast::Identifier>> &parameters, const std::unordered_map<std::string, std::shared_ptr<ast::Expression>> &defaults, const std::shared_ptr<ast::Block> &body, const std::shared_ptr<evaluator::Environment> &env); // function对象初始化函数
            virtual std::string toString() const;                                                                                                                                                                                                                                                        // function对象返回值字符串化函数
            virtual void print() const;                                                                                                                                                                                                                                                                  // function对象返回值打印函数
            virtual HashKey hashKey() const;                                                                                                                                                                                                                                                             // function对象哈希键值获取函数

        public:
            /* 公有成员变量 */
            std::string name;                                                           // Function对象的函数名
            std::vector<std::shared_ptr<ast::Identifier>> parameters;                   // Function对象的参数列表
            std::unordered_map<std::string, std::shared_ptr<ast::Expression>> defaults; // Function对象的默认参数
            std::shared_ptr<ast::Block> body;                                           // Function对象的函数体
            std::shared_ptr<evaluator::Environment> env;                                // Function对象指向外部环境的指针
        };
    }
}