
/*
 * If this file is included multiple times (directly or via other headers),
 * the compiler would try to process it multiple times, leading to redefinition errors.
 * The guard (ifndef NAV2_ASTAR_PLANNER__ASTAR_PLANNER_HPP_) ensures it's included only once, preventing conflicts.
 */
#ifndef NAV2_ASTAR_PLANNER__ASTAR_PLANNER_HPP_
#define NAV2_ASTAR_PLANNER__ASTAR_PLANNER_HPP_

#include <string>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

#include "nav2_core/global_planner.hpp"
#include "nav_msgs/msg/path.hpp"
#include "nav2_util/robot_utils.hpp"
#include "nav2_util/lifecycle_node.hpp"
#include "nav2_costmap_2d/costmap_2d_ros.hpp"

namespace nav2_astar_planner
{

    // a class named AStar that inherits from nav2_core::GlobalPlanner
    class AStar : public nav2_core::GlobalPlanner
    {
    public:
        AStar() = default;
        ~AStar() = default;

        // plugin configure
        void configure(const rclcpp_lifecycle::LifecycleNode::WeakPtr &parent,
                       std::string name, std::shared_ptr<tf2_ros::Buffer> tf,
                       std::shared_ptr<nav2_costmap_2d::Costmap2DROS> costmap_ros) override;

        // plugin cleanup
        void cleanup() override;

        // plugin activate
        void activate() override;

        // plugin deactivate
        void deactivate() override;

        // This method creates path for given start and goal pose.
        nav_msgs::msg::Path createPlan(
            const geometry_msgs::msg::PoseStamped &start,
            const geometry_msgs::msg::PoseStamped &goal) override;

    private:
        // TF buffer
        std::shared_ptr<tf2_ros::Buffer> tf_;
        
        // node ptr
        nav2_util::LifecycleNode::SharedPtr node_;
        
        /*
        Global Costmap: costmap_ is a pointer to an instance of Costmap2D. Instead of storing the object itself, it holds a memory address where the object is located.
        */
        nav2_costmap_2d::Costmap2D * costmap_;
        
        // The global frame of the costmap
        std::string global_frame_, name_;

        double interpolation_resolution_;
    };

} // namespace nav2_astar_planner

#endif // NAV2_ASTAR_PLANNER__ASTAR_PLANNER_HPP_