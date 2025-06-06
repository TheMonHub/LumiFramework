# LumiFramework

## LumiFramework: A C++ Framework Library for Desktop Applications
[![codecov](https://codecov.io/gh/TheMonHub/LumiFramework/graph/badge.svg?token=2YN92BA4JE)](https://codecov.io/gh/TheMonHub/LumiFramework)

Lumi is a **C++ framework library** meticulously designed to simplify and accelerate the development of **robust,
high-performance, and interactive cross-platform desktop applications**. It functions as a powerful library that
provides the foundational structure and utilities typically found in a full-fledged framework, all while maintaining the
flexibility and control characteristic of a well-designed library. Lumi's primary goal is to significantly reduce
boilerplate code and abstract away common complexities, allowing developers to dedicate their focus to the unique logic
and innovation of their applications.

### Core Philosophy & Features

Lumi achieves its mission by adhering to a clear philosophy and offering distinct features:

* **Designed for Low-Level Control with Optional High-Level Framework Features:** Lumi is fundamentally built to provide
  developers with granular control over low-level aspects of application development. Simultaneously, it offers optional
  higher-level abstractions and framework-like components, such as a core application loop, event handling mechanisms,
  and rendering pipeline integration. This dual approach allows developers to choose their desired level of abstraction,
  enabling direct low-level manipulation when needed, or leveraging convenient high-level features for rapid
  development.

* **A Library Acting as a Framework:** Lumi provides a comprehensive set of building blocks and higher-level
  abstractions, including a core application loop, event handling mechanisms, and rendering pipeline integration. These
  components are offered as part of the library, allowing developers to adopt as much or as little of the "framework"
  structure as their project requires. You can leverage Lumi for its opinionated defaults for rapid development, or
  integrate its individual components into an existing architecture.

* **Curated Cross-Platform Foundation:** At its heart, Lumi provides robust, cross-platform abstractions for fundamental
  desktop application elements such as window management, input handling, and graphics context creation. It
  intelligently integrates and builds upon **preselected, battle-tested low-level libraries** (like GLFW) and direct
  system APIs. This eliminates the burden on developers to research, select, and integrate these complex foundational
  components from scratch, ensuring a stable and performant base.

* **Modularity & Developer Control:** Lumi is built with supreme modularity in mind. It is provided as **static libraries**, Unlike monolithic frameworks
  that often dictate your application's entire architecture, Lumi adapts to *your* application's logic. It provides
  granular, lower-level access, empowering you to easily swap out default implementations, integrate other third-party
  libraries seamlessly, or inject your own custom solutions precisely where your application demands it.

* **Empowering C++ Developers:** Lumi is crafted by C++ developers, for C++ developers. While it offers essential
  scaffolding and higher-level abstractions (such as a core application loop and event dispatching), it ensures you
  remain entirely in charge of your application's unique features and core work. Lumi integrates smoothly into your
  existing C++ environment, empowering you to craft your own application architecture, rendering strategies, and overall
  logic with **significantly less complexity and a heightened level of focus**.

### Vision & Goals

LumiFramework is born from the desire to make advanced C++ desktop application development more accessible and
enjoyable, without compromising on performance or developer control. Our vision for LumiFramework is to be:

* **The Premier Foundation for Desktop C++:** A trusted, reliable, and continuously evolving core for building a diverse
  range of desktop applications, from powerful utilities to immersive interactive experiences. We are explicitly focused
  on **Windows, Linux, and macOS** as our primary target platforms.

* **Truly Developer-Centric:** We believe developers should spend their time solving unique problems, not wrestling with
  boilerplate or rigid framework structures. Lumi will always prioritize developer autonomy, offering powerful tools and
  sensible defaults that can be easily customized or bypassed, ensuring it complements your workflow.

* **A Catalyst for Innovation:** By simplifying the underlying complexities of cross-platform setup and low-level
  interactions, Lumi aims to empower developers to bring their unique ideas to life faster, fostering greater innovation
  within the C++ desktop application space.

* **Modular & Extensible:** Lumi will consistently strive for maximum modularity, allowing developers to integrate their
  preferred libraries and custom implementations seamlessly. This means Lumi will always be a complementary tool within
  your existing C++ ecosystem, not a restrictive replacement.

### Project Status

LumiFramework is currently in its **active development and execution phase**. Our primary focus is on building a robust
and stable **core foundation** and establishing its key features.

At this time, we are **not yet accepting external contributions**. We appreciate your interest, and comprehensive
contribution guidelines (along with a code of conduct) will be made available once the project reaches a more mature and
stable state.
