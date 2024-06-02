{
  description = "Xv6 for Riscv64 flake. Run 'make qemu' to boot the kernel.";
  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = nixpkgs.legacyPackages.${system};
      # Cross compiler for riscv.
      riscv64-gcc11 = pkgs.pkgsCross.riscv64.buildPackages.gcc11;
    in
    {
      devShell = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          qemu
          riscv64-gcc11
          clang-tools
        ];
      };
    }
  );
}
