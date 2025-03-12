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
        commit = "5927a2e797b89fd186cd31c908ff23f1295c8038",
        sha256 = "3a141eda19842e792bee614a47ba5909c4a3d784779b02978c3cc5d8a45f7ffa",  # noqa
        build_file = ":package.BUILD.bazel",
        mirrors = mirrors,
    )
