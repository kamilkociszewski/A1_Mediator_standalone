from typing import Any, Dict, Optional
from fastapi import FastAPI, HTTPException, Path, Body
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel, Field, model_validator  # Updated import for Pydantic V2

app = FastAPI()

# Add CORS middleware
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # Adjust to specific domains if needed
    allow_credentials=True,
    allow_methods=["*"],  # Explicitly allow PUT, GET, etc.
    allow_headers=["*"],  # Allow custom headers like Content-Type
)

class CreateSchema(BaseModel):
    schema_: Optional[str] = Field(alias="$schema", default="http://json-schema.org/draft-07/schema#")  # Avoid shadowing
    type: str = "object"
    properties: Dict[str, Dict[str, Any]] = Field(default_factory=dict)  # Allows dynamic properties
    additionalProperties: bool = False

    @model_validator(mode="before")
    def validate_properties(cls, values):
        """Ensure all properties are of types integer or bool."""
        properties = values.get("properties", {})
        for prop_name, prop_details in properties.items():
            if "type" not in prop_details or prop_details["type"] not in ["integer", "bool"]:
                raise ValueError(f"Invalid property type for '{prop_name}'. Only 'integer' and 'bool' are allowed.")
        return values

class PolicyTypeSchema(BaseModel):
    name: str
    description: str
    policy_type_id: int = 10000
    create_schema: CreateSchema = None

class PolicyInstanceSchema(BaseModel):
    data: Dict[str, Any]  # Accepts dynamic fields for policy instances

policy_types = {}
policy_instances = {}

@app.get("/a1-p/healthcheck")
async def get_healthcheck():
    return {"status": "A1 is healthy"}

@app.get("/a1-p/policytypes", response_model=list[int])
async def get_all_policy_types():
    return list(policy_types.keys())

@app.get("/a1-p/policytypes/{policy_type_id}", response_model=PolicyTypeSchema)
async def get_policy_type(policy_type_id: int = Path(..., gt=0, lt=2147483647)):
    if policy_type_id not in policy_types:
        raise HTTPException(status_code=404, detail="Policy type not found")
    return policy_types[policy_type_id]

@app.put("/a1-p/policytypes/{policy_type_id}", response_model=PolicyTypeSchema)
async def create_policy_type(policy_type_id: int = Path(..., gt=0, lt=2147483647),
                             body: PolicyTypeSchema = Body(...)):
    if policy_type_id in policy_types:
        raise HTTPException(status_code=400, detail="Policy type already exists")
    policy_types[policy_type_id] = body
    policy_instances[policy_type_id] = {}
    return body


@app.put("/a1-p/policytypes/{policy_type_id}/policies/{policy_instance_id}", response_model=PolicyInstanceSchema)
async def create_policy_instance(
    policy_type_id: int,
    policy_instance_id: str,
    body: PolicyInstanceSchema = Body(...),
):
    # Check if policy type exists
    if policy_type_id not in policy_types:
        raise HTTPException(status_code=404, detail="Policy type does not exist")

    # Fetch the policy type's schema
    policy_type = policy_types[policy_type_id]
    schema_properties = policy_type.create_schema.properties

    # Validate each field in the instance against the schema
    for field_name, field_value in body.data.items():
        if field_name not in schema_properties:
            raise HTTPException(status_code=400, detail=f"Field '{field_name}' is not allowed for this policy type")
        expected_type = schema_properties[field_name]["type"]
        if expected_type == "integer" and not isinstance(field_value, int):
            raise HTTPException(status_code=400, detail=f"Field '{field_name}' must be an integer")
        if expected_type == "bool" and not isinstance(field_value, bool):
            raise HTTPException(status_code=400, detail=f"Field '{field_name}' must be a boolean")

    # Save the instance under the policy type
    policy_instances[policy_type_id][policy_instance_id] = body

    return body


@app.get("/a1-p/policytypes/{policy_type_id}/policies/{policy_instance_id}/status")
async def get_policy_instance_status(policy_type_id: int, policy_instance_id: str):
    if policy_type_id not in policy_types:
        raise HTTPException(status_code=404, detail="Policy type does not exist")
    if policy_instance_id not in policy_instances[policy_type_id]:
        raise HTTPException(status_code=404, detail="Policy instance does not exist")

    return {"data": policy_instances[policy_type_id][policy_instance_id].data}


@app.get("/a1-p/policytypes/{policy_type_id}/policies", response_model=list[str])
async def list_policy_instances(policy_type_id: int):
    if policy_type_id not in policy_types:
        raise HTTPException(status_code=400, detail="Policy type does not exist")
    return list(policy_instances[policy_type_id].keys())

@app.delete("/a1-p/policytypes/{policy_type_id}")
async def delete_policy_type(policy_type_id: int = Path(..., gt=0, lt=2147483647)):
    if policy_type_id not in policy_types:
        raise HTTPException(status_code=404, detail="Policy type not found")
    if policy_type_id in policy_instances and policy_instances[policy_type_id]:
        raise HTTPException(status_code=400, detail="Policy type cannot be deleted because there are instances")
    del policy_types[policy_type_id]
    return {"detail": "Policy type successfully deleted"}

@app.delete("/a1-p/policytypes/{policy_type_id}/policies/{policy_instance_id}")
async def delete_policy_instance(policy_type_id: int, policy_instance_id: str):
    if policy_type_id not in policy_types:
        raise HTTPException(status_code=404, detail="Policy type not found")
    if policy_instance_id not in policy_instances[policy_type_id]:
        raise HTTPException(status_code=400, detail="Policy instance not found")
    del policy_instances[policy_type_id][policy_instance_id]
    return {"detail": "Policy instance successfully deleted"}

if __name__ == "__main__":
    import uvicorn  # Ensure import is included
    uvicorn.run(app, host="0.0.0.0", port=9000)
