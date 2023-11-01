{
  description = "Xv6 for Riscv64 flake. Run 'make qemu' to boot the kernel.";
  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = nixpkgs.legacyPackages.${system};
      pkgsCross = pkgs.pkgsCross.riscv64;
    in
    {
      devShell = pkgs.mkShell {
        nativeBuildInputs = [
          pkgs.qemu
          pkgsCross.buildPackages.gcc11
        ];
      };
    }
  );
}
