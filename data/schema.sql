PRAGMA foreign_keys = ON;


-- =========================================
-- PROJECTS
-- =========================================

CREATE TABLE IF NOT EXISTS projects (
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    name TEXT NOT NULL,
    description TEXT,
    location TEXT,

    start_date TEXT,
    end_date TEXT,

    status TEXT NOT NULL DEFAULT 'planned'
        CHECK (
            status IN (
                'planned',
                'active',
                'on_hold',
                'completed',
                'cancelled'
            )
        ),

    budget REAL NOT NULL DEFAULT 0
        CHECK (budget >= 0),

    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);


-- ===============================================
-- TASKS
-- ===============================================

CREATE TABLE IF NOT EXISTS tasks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    project_id INTEGER NOT NULL,

    name TEXT NOT NULL,
    description TEXT,

    status TEXT NOT NULL DEFAULT 'todo'
        CHECK (
            status IN (
                'todo',
                'in_progress',
                'blocked',
                'completed',
                'cancelled'
            )
        ),

    priority TEXT NOT NULL DEFAULT 'medium'
        CHECK (
            priority IN (
                'low',
                'medium',
                'high',
                'critical'
            )
        ),

    start_date TEXT,
    due_date TEXT,
    completed_at TEXT,

    estimated_cost REAL NOT NULL DEFAULT 0
        CHECK (estimated_cost >= 0),

    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY (project_id)
        REFERENCES projects(id)
        ON DELETE CASCADE
);


-- ================================================
-- WORKERS
-- ================================================

CREATE TABLE IF NOT EXISTS workers (
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,

    email TEXT UNIQUE,
    phone TEXT,

    role TEXT,

    hourly_rate REAL NOT NULL DEFAULT 0
        CHECK (hourly_rate >= 0),

    active INTEGER NOT NULL DEFAULT 1
        CHECK (active IN (0, 1)),

    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);


-- ================================================
-- PROJECT / WORKER ASSIGNMENTS
-- ================================================

CREATE TABLE IF NOT EXISTS project_workers (
    project_id INTEGER NOT NULL,
    worker_id INTEGER NOT NULL,

    assigned_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,

    PRIMARY KEY (project_id, worker_id),

    FOREIGN KEY (project_id)
        REFERENCES projects(id)
        ON DELETE CASCADE,

    FOREIGN KEY (worker_id)
        REFERENCES workers(id)
        ON DELETE CASCADE
);


-- ==========================================
-- TASK / WORKER ASSIGNMENTS
-- ==========================================

CREATE TABLE IF NOT EXISTS task_workers (
    task_id INTEGER NOT NULL,
    worker_id INTEGER NOT NULL,

    assigned_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,

    PRIMARY KEY (task_id, worker_id),

    FOREIGN KEY (task_id)
        REFERENCES tasks(id)
        ON DELETE CASCADE,

    FOREIGN KEY (worker_id)
        REFERENCES workers(id)
        ON DELETE CASCADE
);


-- ============================================
-- COST ENTRIES
-- ============================================

CREATE TABLE IF NOT EXISTS cost_entries (
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    project_id INTEGER NOT NULL,
    task_id INTEGER,

    category TEXT NOT NULL
        CHECK (
            category IN (
                'labor',
                'material',
                'equipment',
                'subcontractor',
                'permit',
                'transportation',
                'other'
            )
        ),

    description TEXT,

    amount REAL NOT NULL
        CHECK (amount >= 0),

    entry_date TEXT NOT NULL DEFAULT CURRENT_DATE,

    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY (project_id)
        REFERENCES projects(id)
        ON DELETE CASCADE,

    FOREIGN KEY (task_id)
        REFERENCES tasks(id)
        ON DELETE SET NULL
);


-- ===========================================
-- INCIDENTS
-- ===========================================

CREATE TABLE IF NOT EXISTS incidents (
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    project_id INTEGER NOT NULL,

    task_id INTEGER,
    worker_id INTEGER,

    title TEXT NOT NULL,
    description TEXT NOT NULL,

    incident_type TEXT NOT NULL DEFAULT 'other'
        CHECK (
            incident_type IN (
                'injury',
                'safety',
                'equipment',
                'property_damage',
                'near_miss',
                'other'
            )
        ),

    severity TEXT NOT NULL DEFAULT 'low'
        CHECK (
            severity IN (
                'low',
                'medium',
                'high',
                'critical'
            )
        ),

    incident_date TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,

    resolved INTEGER NOT NULL DEFAULT 0
        CHECK (resolved IN (0, 1)),

    resolution_notes TEXT,

    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY (project_id)
        REFERENCES projects(id)
        ON DELETE CASCADE,

    FOREIGN KEY (task_id)
        REFERENCES tasks(id)
        ON DELETE SET NULL,

    FOREIGN KEY (worker_id)
        REFERENCES workers(id)
        ON DELETE SET NULL
);


-- =============================================
-- INDEXES
-- =============================================

CREATE INDEX IF NOT EXISTS idx_tasks_project_id
    ON tasks(project_id);

CREATE INDEX IF NOT EXISTS idx_tasks_status
    ON tasks(status);

CREATE INDEX IF NOT EXISTS idx_cost_entries_project_id
    ON cost_entries(project_id);

CREATE INDEX IF NOT EXISTS idx_cost_entries_task_id
    ON cost_entries(task_id);

CREATE INDEX IF NOT EXISTS idx_incidents_project_id
    ON incidents(project_id);

CREATE INDEX IF NOT EXISTS idx_incidents_worker_id
    ON incidents(worker_id);

CREATE INDEX IF NOT EXISTS idx_project_workers_worker_id
    ON project_workers(worker_id);

CREATE INDEX IF NOT EXISTS idx_task_workers_worker_id
    ON task_workers(worker_id);