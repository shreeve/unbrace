# encoding: utf-8

Gem::Specification.new do |s|
  s.name        = "unbrace"
  s.version     = `grep -m 1 '^// Version:' ext/unbrace/unbrace.c | cut -f 3 -d ' '`
  s.author      = "Steve Shreeve"
  s.email       = "steve.shreeve@gmail.com"
  s.summary     = "A Ruby gem that expands braces in strings"
  s.description = "Expand braces, similar to a file glob"
  s.homepage    = "https://github.com/shreeve/unbrace"
  s.license     = "MIT"
  s.platform    = Gem::Platform::RUBY
  s.files       = `git ls-files`.split("\n") - %w[.gitignore]
  s.extensions << 'ext/unbrace/extconf.rb'
  s.add_development_dependency "bundler", "~> 2.0"
  s.add_development_dependency "rake", "~> 13.1"
  s.add_development_dependency "rake-compiler", "~> 1.2"
  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
end
