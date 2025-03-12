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

// Returns an offset pointer inside message that skips over leading newlines.
const char* ltrim(const char* message) {
  while (*message == '\n') {
    ++message;
  }
  return message;
}

int do_main() {
  auto meshcat = std::make_shared<Meshcat>();

  // Add a mouse teleop controller that can be dragged in the XY plane

  // Create a cylinder object
  const std::string cylinder_path = "/drake/red_cylinder";
  const double cylinder_radius = 0.1;
  const double cylinder_length = 0.2;
  const Rgba cylinder_rgba = Rgba(1, 0, 0);
  const Cylinder cylinder (cylinder_radius, cylinder_length);
  meshcat->SetObject(cylinder_path, cylinder, cylinder_rgba);

  // Set cylinder above the XY plane.
  const std::vector<double> cylinder_position {0, 0, 0.5 * cylinder_length};
  meshcat->SetProperty(cylinder_path, "position", cylinder_position);

  // Make cylinder draggable by adding mouse teleop controls.
  const Vector3d drag_plane_normal{0, 0, 1};  // XY plane
  meshcat->AddMouseTeleop("draggable_cylinder", cylinder_path,
                          drag_plane_normal);

  std::cout << "\n\nOpen your browser to the URL:" << meshcat->web_url() << "\n";

  std::cout << ltrim(R"""(
- A red draggable cylinder has been added.
- Click and drag the cylinder to move it around.
- The cylinder should only move horizontally (in the XY plane).
- When you hover over the cylinder, it should have a subtle glow effect.
)""");
  MaybePauseForUser();

  // Display the current position of the mouse teleop controller in a loop
  std::cout << "Starting position tracking loop. Press Ctrl+C to exit.\n";
  try {
    while (true) {
      Vector3d current_position = meshcat->GetMouseTeleopTranslation("draggable_cylinder");
      // Clear the previous line and print the updated position
      std::cout << "\rCurrent position: ["
                << current_position.x() << ", "
                << current_position.y() << ", "
                << current_position.z() << "]    " << std::flush;
      
      // Sleep briefly to avoid flooding the console
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  } catch (const std::exception& e) {
    std::cout << "\nPosition tracking stopped: " << e.what() << std::endl;
  }

  return 0;
}

}  // namespace
}  // namespace geometry
}  // namespace drake

int main() {
  return drake::geometry::do_main();
}
