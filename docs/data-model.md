The Construction Dashboard uses five primary domain entities:

- Project
- Task
- CostEntry
- Worker
- Incident

SQLite is used for local application persistence.


## Project itself

Represents a construction project.

A project contains tasks, costs, workers, and incidents.

### Important fields

- id
- name
- description
- location
- startDate
- endDate
- status
- budget


## Task

Represents work that must be performed for a project.

Each task belongs to exactly one project.

A project can contain many tasks.

### Relationship

Project 1 -> many Tasks

### Important fields

- id
- projectId
- name
- description
- status
- priority
- startDate
- dueDate
- completedAt
- estimatedCost

## CostEntry

Represents an expense associated with construction work.

Every cost entry belongs to a project.

A cost entry may optionally belong to a task.

### Relationship

Project 1 -> many CostEntries

Task 1 -> many CostEntries

### Categories

- labor
- material
- equipment
- subcontractor
- permit
- transportation
- other

## Worker

Represents a worker participating in construction projects.

Workers may participate in multiple projects and multiple tasks.

### Relationships

Worker many <-> many Project

Worker many <-> many Task

The database implements these relationships using:

- project_workers
- task_workers

## Incident

Represents a safety or operational incident.

An incident always belongs to a project.

It may optionally reference a task and/or worker.

### Incident types

- injury
- safety
- equipment
- property_damage
- near_miss
- other

### Severity

- low
- medium
- high
- critical

## Entity Relationships

Project
  |
  +-- Task
  |
  +-- CostEntry
  |
  +-- Incident
  |
  +-- ProjectWorker -- Worker

Task
  |
  +-- CostEntry
  |
  +-- Incident
  |
  +-- TaskWorker -- Worker

## Database

SQLite is used through the Qt SQL module

Qt dependency:

Qt6::Sql

SQLite will be accessed using QSqlDatabase with the QSQLITE driver