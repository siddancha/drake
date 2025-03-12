load("//tools/workspace:github.bzl", "github_archive")

def meshcat_repository(
        name,
        mirrors = None):
    github_archive(
        name = name,
        repository = "siddancha/meshcat",
        upgrade_advice = """
        Updating this commit requires local testing; see
        drake/tools/workspace/meshcat/README.md for details.
        """,
        commit = "d2657861a2898f1b466fe6a90dc50b6c968d59b0",
        sha256 = "4949a3c0f15525bd6288e82e320d77d57bc25f6a700363e4cdacec83f81dbc65",  # noqa
        build_file = ":package.BUILD.bazel",
        mirrors = mirrors,
    )
