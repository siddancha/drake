#include "drake/geometry/meshcat.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>

#include <gtest/gtest.h>

#include "drake/common/find_resource.h"
#include "drake/common/test_utilities/maybe_pause_for_user.h"
#include "drake/geometry/meshcat_visualizer.h"
#include "drake/geometry/rgba.h"
#include "drake/math/rigid_transform.h"
#include "drake/math/rotation_matrix.h"

using drake::geometry::Meshcat;
using drake::geometry::MeshcatVisualizer;
using drake::geometry::Rgba;
using drake::math::RigidTransformd;
using drake::math::RotationMatrixd;
using Eigen::Vector3d;

namespace drake {
namespace geometry {
namespace {

using common::MaybePauseForUser;

// Utility function to trim leading whitespace from a multi-line string.
std::string ltrim(std::string text) {
  std::istringstream iss(text);
  std::string result;
  std::string line;
  while (std::getline(iss, line)) {
    if (!result.empty()) {
      result += "\n";
    }
    // Find the first non-whitespace character.
    size_t pos = line.find_first_not_of(" \t");
    if (pos != std::string::npos) {
      result += line.substr(pos);
    } else {
      result += line;
    }
  }
  return result;
}

int do_main() {
  auto meshcat = std::make_shared<Meshcat>();

  // Add a mouse teleop controller that can be dragged in the XY plane
  {
    // Create a draggable cylinder with the Z-axis as the drag plane normal
    const double cylinder_radius = 0.1;
    const double cylinder_length = 0.2;
    const Vector3d teleop_position{0, 0, 0.5};
    const RigidTransformd teleop_transform(teleop_position);
    const Vector3d drag_plane_normal{0, 0, 1};  // XY plane

    meshcat->AddMouseTeleop("draggable_cylinder", "mouse_teleop", 
                            cylinder_radius, cylinder_length,
                            teleop_transform, drag_plane_normal);

    std::cout << "- A red draggable cylinder has been added. You can click and drag it "
              << "along the XY plane.\n";
  }

  std::cout << "\nOpen your browser to the URL:\n\n"
            << meshcat->web_url() << "\n\n";

  std::cout << ltrim(R"""(
- You should see a red cylinder that can be dragged in the XY plane.
- Click and drag the cylinder to move it around.
- The cylinder should only move horizontally (in the XY plane).
- When you hover over the cylinder, it should have a subtle glow effect.
)""");
  MaybePauseForUser();

  // Display the current position of the mouse teleop controller
  // Vector3d current_position = meshcat->GetMouseTeleopTranslation("draggable_cylinder");
  // std::cout << "Current position of the draggable cylinder: ["
  //           << current_position.x() << ", "
  //           << current_position.y() << ", "
  //           << current_position.z() << "]\n";

  MaybePauseForUser();
  return 0;
}

}  // namespace
}  // namespace geometry
}  // namespace drake

int main() {
  return drake::geometry::do_main();
}
