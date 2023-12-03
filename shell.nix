{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = [];
		shellHook = ''
			alias cr="clear; g++ run.cpp -o run; ./run"
		'';
}

