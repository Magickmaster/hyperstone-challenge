{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [ gcc ];

  shellHook = ''
    echo "Welcome to the C development shell!"
  '';
}