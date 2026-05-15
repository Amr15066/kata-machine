// =============================================
// DSA in Rust — Practice & Solutions
// =============================================
// By default, the practice modules are active.
// Fill in the TODO stubs, then run: cargo test
//
// To run the solution tests instead:
//   cargo test --features solutions
//
// To check a single module:
//   cargo test linear_search

// Switch between practice and solutions with a feature flag
#[cfg(not(feature = "solutions"))]
#[path = "practice/mod.rs"]
pub mod dsa;

#[cfg(feature = "solutions")]
#[path = "solutions/mod.rs"]
pub mod dsa;
